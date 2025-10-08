#include "Player.h"
#include "MathUtil.h"
#include <algorithm>

using namespace KamataEngine;

void Player::Initialize() {
	input_ = Input::GetInstance();

	// --- モデル読み込み（Resources/player/player.obj を読み込み）---
	model_ = Model::CreateFromOBJ("player", /*smoothing=*/true);

	// --- ワールド変換 ---
	world_.Initialize();
	world_.scale_ = {0.8f, 0.8f, 0.8f};
	world_.translation_ = {0.0f, 0.5f, 0.0f};
	// Blender上で右(+X)を正面に作った場合、初期向き補正を入れるなら↓
	// world_.rotation_.y = MathUtil::kPi * 0.5f;
	world_.TransferMatrix();

	// --- ゲームパッドのデッドゾーン ---
	input_->SetJoystickDeadZone(0, deadZoneL_, deadZoneL_);
}

void Player::Update(float dt) {
	// --- 入力（キーボード）---
	float ax = 0.0f;
	float az = 0.0f;

	if (input_->PushKey(DIK_LEFT) || input_->PushKey(DIK_A))
		ax -= 1.0f;
	if (input_->PushKey(DIK_RIGHT) || input_->PushKey(DIK_D))
		ax += 1.0f;
	if (input_->PushKey(DIK_UP) || input_->PushKey(DIK_W))
		az += 1.0f;
	if (input_->PushKey(DIK_DOWN) || input_->PushKey(DIK_S))
		az -= 1.0f;

	// --- 入力（ゲームパッド：左スティック）---
	XINPUT_STATE pad{};
	if (input_->GetJoystickState(0, pad)) {
		const SHORT lx = pad.Gamepad.sThumbLX;
		const SHORT ly = pad.Gamepad.sThumbLY;
		// XInputは上が+Yなので、ゲーム座標のz+へ進むようlyを加算方向に
		const float nx = std::clamp(lx / 32768.0f, -1.0f, 1.0f);
		const float ny = std::clamp(ly / 32768.0f, -1.0f, 1.0f);

		// デッドゾーン処理（手動）
		auto dead = [this](float v) {
			float t = static_cast<float>(deadZoneL_) / 32768.0f;
			if (std::fabs(v) < t)
				return 0.0f;
			// 線形再マッピング
			float s = (std::fabs(v) - t) / (1.0f - t);
			return (v > 0.0f ? s : -s);
		};

		ax += dead(nx);
		az += dead(ny);
	}

	// --- 正規化（斜め移動で速くならないように）---
	float len2 = ax * ax + az * az;
	if (len2 > 1.0f) {
		float inv = 1.0f / std::sqrt(len2);
		ax *= inv;
		az *= inv;
	}

	// --- 目標速度 ---
	Vector3 targetVel{ax * moveSpeed_, 0.0f, az * moveSpeed_};

	// --- 簡易ダンピング補間 ---
	float t = std::clamp(damp_ * dt, 0.0f, 1.0f);
	vel_.x = vel_.x + (targetVel.x - vel_.x) * t;
	vel_.y = 0.0f;
	vel_.z = vel_.z + (targetVel.z - vel_.z) * t;

	// --- 位置更新 ---
	world_.translation_.x += vel_.x * dt;
	world_.translation_.z += vel_.z * dt;

	// --- 向き更新（右移動＝右向きになる）---
	if (std::fabs(vel_.x) + std::fabs(vel_.z) > 0.001f) {
		// モデルの正面が +X の場合（Blenderで右を正面にしている）
		float yaw = std::atan2(vel_.z, vel_.x);
		world_.rotation_.y = yaw;

		// モデルの正面が +Z なら下記の式に変更：
		// float yaw = std::atan2(vel_.x, vel_.z);
	}

	// --- 行列更新＆転送 ---
	world_.matWorld_ = MathUtil::MakeAffineMatrix(world_.scale_, world_.rotation_, world_.translation_);
	world_.TransferMatrix();
}

void Player::Draw(const Camera& camera) const { model_->Draw(world_, camera); }

void Player::Finalize() {
	delete model_;
	model_ = nullptr;
}

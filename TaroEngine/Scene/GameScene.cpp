#include "GameScene.h"
#include "Player.h"
#include "SceneId.h"
#include <KamataEngine.h>
#include <algorithm>
#include <cmath>

using namespace KamataEngine;

void GameScene::Initialize() {
	player_ = std::make_unique<Player>();
	player_->Initialize();

	camera_ = std::make_unique<Camera>();
	camera_->translation_ = {0.0f, 2.0f, -6.0f};
	camera_->rotation_ = {0.3f, 0.0f, 0.0f}; // 軽く下向きに
	camera_->Initialize();
}

std::optional<SceneId> GameScene::Update(float dt) {
	player_->Update(dt);

	// プレイヤー追従：位置のみ
	const Vector3 p = player_->GetPosition();
	const Vector3 desired = {p.x, p.y + 2.0f, p.z - 6.0f};

	const float k = std::clamp(8.0f * dt, 0.0f, 1.0f);
	camera_->translation_.x += (desired.x - camera_->translation_.x) * k;
	camera_->translation_.y += (desired.y - camera_->translation_.y) * k;
	camera_->translation_.z += (desired.z - camera_->translation_.z) * k;

	// プレイヤーの方向を向くように Y 回転を合わせる（簡易）
	const Vector3 dir = {p.x - camera_->translation_.x, 0.0f, p.z - camera_->translation_.z};
	if (std::fabs(dir.x) + std::fabs(dir.z) > 0.0001f) {
		camera_->rotation_.y = std::atan2(dir.x, dir.z);
	}

	// カメラ行列を更新＆GPUへ転送
	camera_->UpdateMatrix();
	camera_->TransferMatrix();

	return std::nullopt;
}

void GameScene::Draw() {
	Model::PreDraw();
	player_->Draw(*camera_);
	Model::PostDraw();
}

void GameScene::Finalize() {
	if (player_) {
		player_->Finalize();
		player_.reset();
	}

	camera_.reset();
}

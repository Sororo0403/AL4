#include "Skydome.h"
#include <memory> // unique_ptr 用

using namespace KamataEngine;

void Skydome::Initialize() {
	// モデル生成（右手系 / 反転等はプロジェクト規約に合わせて true/false を選択）
	model_.reset(Model::CreateFromOBJ("skydome"));

	// ワールド変換の初期化
	worldTransform_.Initialize();
	worldTransform_.translation_ = {0.0f, 0.0f, 0.0f};
}

void Skydome::Update() {
	// 行列更新＆GPU へ転送
	worldTransform_.TransferMatrix();
}

void Skydome::Draw(const KamataEngine::Camera& camera) const {
	// 依存が揃っているときのみ描画
	if (!model_) {
		return;
	}

	// 注意：Model::PreDraw/PostDraw は外部（シーン側）で呼ぶ想定
	model_->Draw(worldTransform_, camera);
}

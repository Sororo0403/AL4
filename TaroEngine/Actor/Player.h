#pragma once
#include <KamataEngine.h>

/// <summary>
/// A01: 自キャラ操作（カーソル／スティックで移動）
/// </summary>
class Player {
public:
	void Initialize();
	void Update(float dt);
	void Draw(const KamataEngine::Camera& camera) const;
	void Finalize();

	// 位置を外から参照（カメラ追従など）
	const KamataEngine::Vector3& GetPosition() const { return world_.translation_; }

private:
	KamataEngine::Model* model_ = nullptr;
	KamataEngine::WorldTransform world_{};

	// 移動パラメータ
	float moveSpeed_ = 3.5f; // m/s 相当（任意）
	float damp_ = 12.0f;     // 減衰（補間用）
	KamataEngine::Vector3 vel_{0, 0, 0};

	// 入力
	KamataEngine::Input* input_ = nullptr;

	// XInputのスティックデッドゾーン
	int32_t deadZoneL_ = 6000; // 0〜32768（適宜調整）
};

#pragma once
#include <KamataEngine.h>

/// <summary>
/// A01: 自キャラ操作クラス（カーソル／スティックで移動）
/// </summary>
class Player {
public:
	/// <summary>
	/// 初期化処理を行います。
	/// </summary>
	void Initialize();

	/// <summary>
	/// フレーム更新処理を行います。
	/// </summary>
	/// <param name="dt">前フレームからの経過時間（秒）</param>
	void Update(float dt);

	/// <summary>
	/// モデルを描画します。
	/// </summary>
	/// <param name="camera">描画に使用するカメラ</param>
	void Draw(const KamataEngine::Camera& camera) const;

	/// <summary>
	/// 終了処理を行います。
	/// </summary>
	void Finalize();

	/// <summary>
	/// 現在位置を取得します。（カメラ追従などで使用）
	/// </summary>
	const KamataEngine::Vector3& GetPosition() const { return world_.translation_; }

private:
	// モデル
	KamataEngine::Model* model_ = nullptr;

	// ワールド変換
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

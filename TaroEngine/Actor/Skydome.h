#pragma once
#include <KamataEngine.h>

/// <summary>
/// 天球を描画するクラス。
/// </summary>
class Skydome final {
public:
	/// <summary>
	/// デフォルトデストラクタ。
	/// </summary>
	~Skydome() = default;

	/// <summary>
	/// 初期化処理。
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム更新処理。
	/// </summary>
	void Update();

	/// <summary>
	/// 描画処理。
	/// </summary>
	/// <param name="camera">描画に使用するカメラ</param>
	void Draw(const KamataEngine::Camera& camera) const;

private:
	std::unique_ptr<KamataEngine::Model> model_;
	KamataEngine::WorldTransform worldTransform_;
};

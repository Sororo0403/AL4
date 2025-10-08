#pragma once
#include "IScene.h"
#include "Player.h"
#include "Skydome.h" // 追加

/// <summary>
/// ゲーム本編のシーンクラス。
/// </summary>
class GameScene final : public IScene {
public:
	/// <summary>
	/// シーン開始時に一度だけ呼ばれます。
	/// </summary>
	void Initialize() override;

	/// <summary>
	/// 毎フレーム更新処理を行います。
	/// </summary>
	/// <param name="dt">前フレームからの経過秒</param>
	/// <returns>次のシーンID（切り替えない場合は std::nullopt）</returns>
	std::optional<SceneId> Update(float dt) override;

	/// <summary>
	/// ゲーム中の描画処理を行います。
	/// </summary>
	void Draw() override;

	/// <summary>
	/// シーン終了時の後処理を行います。
	/// </summary>
	void Finalize() override;

private:
	std::unique_ptr<Player> player_;               ///< 自キャラ
	std::unique_ptr<KamataEngine::Camera> camera_; ///< カメラ
	std::unique_ptr<Skydome> skydome_;             ///< 天球
};

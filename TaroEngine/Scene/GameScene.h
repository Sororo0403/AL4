#pragma once
#include "IScene.h"

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
};

#pragma once
#include "IScene.h"

/// <summary>
/// タイトル画面を表すシーンクラス。
/// </summary>
class TitleScene final : public IScene {
public:
	/// <summary>
	/// シーン開始時に一度だけ呼ばれます。
	/// </summary>
	void Initialize() override;

	/// <summary>
	/// 毎フレーム更新処理を行います。
	/// </summary>
	/// <returns>次のシーンID（切り替えない場合は std::nullopt）</returns>
	std::optional<SceneId> Update() override;

	/// <summary>
	/// タイトル画面の描画処理を行います。
	/// </summary>
	void Draw() override;

	/// <summary>
	/// シーン終了時の後処理を行います。
	/// </summary>
	void Finalize() override;
};

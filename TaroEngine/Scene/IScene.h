#pragma once
#include "SceneId.h"
#include <optional>

/// <summary>
/// シーンの共通インターフェイスクラス。すべてのゲームシーンはこのクラスを継承します。
/// </summary>
class IScene {
public:
	/// <summary>
	/// 仮想デストラクタ。
	/// </summary>
	virtual ~IScene() = default;

	/// <summary>
	/// シーン開始時に一度だけ呼ばれます。
	/// </summary>
	virtual void Initialize() {}

	/// <summary>
	/// 毎フレーム更新処理を行います。
	/// </summary>
	/// <param name="dt">前フレームからの経過秒</param>
	/// <returns>次のシーンID（切り替えない場合は std::nullopt）</returns>
	virtual std::optional<SceneId> Update(float dt) = 0;

	/// <summary>
	/// 毎フレームの描画処理を行います。
	/// </summary>
	virtual void Draw() = 0;

	/// <summary>
	/// シーン終了時に一度だけ呼ばれます。
	/// </summary>
	virtual void Finalize() {}
};

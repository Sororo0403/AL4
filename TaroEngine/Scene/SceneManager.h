#pragma once
#include "IScene.h"
#include <functional>
#include <memory>
#include <unordered_map>

/// <summary>
/// シーン生成用のファクトリ関数型。
/// </summary>
using SceneFactory = std::function<std::unique_ptr<IScene>()>;

/// <summary>
/// シーン全体を管理し、現在のシーンの更新・描画を制御するクラス。
/// </summary>
class SceneManager {
public:
	/// <summary>
	/// シーン生成関数を登録します。
	/// </summary>
	/// <param name="id">登録するシーンID。</param>
	/// <param name="factory">シーン生成用ファクトリ関数。</param>
	void Register(SceneId id, SceneFactory factory);

	/// <summary>
	/// 最初に実行するシーンを設定します。
	/// </summary>
	/// <param name="id">最初に起動するシーンID。</param>
	void SetFirst(SceneId id);

	/// <summary>
	/// 現在のシーンを更新します。
	/// </summary>
	/// <param name="dt">前フレームからの経過秒</param>
	void Update(float dt);

	/// <summary>
	/// 現在のシーンの描画を実行します。
	/// </summary>
	void Draw();

private:
	/// <summary>
	/// シーンを切り替えます。
	/// </summary>
	/// <param name="next">切り替えるシーンID。</param>
	void Change(SceneId next);

private:
	std::unordered_map<SceneId, SceneFactory> factories_; ///< シーンIDと生成関数を紐づける連想配列。
	std::unique_ptr<IScene> current_;                     ///< 現在アクティブなシーン。
	SceneId currentId_{};                                 ///< 現在のシーンID。
	bool hasCurrent_{false};                              ///< 現在のシーンが存在するかどうかを示すフラグ。
};

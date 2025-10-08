#include "GameScene.h"
#include "KamataEngine.h"
#include "SceneManager.h"
#include "TitleScene.h"
#include "SceneId.h"
#include <Windows.h>

using namespace KamataEngine;

// Windowsアプリでのエントリーポイント
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int) {
	// --- 1) エンジン初期化 ---
	Initialize(L"KamataEngine シーン制テンプレ");

	// DirectXCommon の取得（描画の開始/終了に使う）
	DirectXCommon* dx = DirectXCommon::GetInstance();

	// --- 1.5) シーン登録 ---
	SceneManager scenes;
	scenes.Register(SceneId::TITLE, [] { return std::make_unique<TitleScene>(); });
	scenes.Register(SceneId::GAME, [] { return std::make_unique<GameScene>(); });
	scenes.SetFirst(SceneId::TITLE);

	// --- 2) メインループ ---
	while (true) {
		// エンジンの毎フレーム更新（true が返ったら終了要求）
		if (Update()) {
			break;
		}

		// 先にロジック（シーン更新・遷移）
		scenes.Update();

		// --- 描画フェーズ ---
		dx->PreDraw();
		scenes.Draw();
		dx->PostDraw();
	}

	// --- 3) 終了処理 ---
	Finalize();
	return 0;
}

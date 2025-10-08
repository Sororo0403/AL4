#include "GameScene.h"
#include "KamataEngine.h"
#include "SceneId.h"
#include "SceneManager.h"
#include "TitleScene.h"
#include <Windows.h>

using namespace KamataEngine;

// Windowsアプリでのエントリーポイント
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int) {
	// --- 1) エンジン初期化 ---
	Initialize(L"KamataEngine");

	// DirectXCommon の取得
	DirectXCommon* dx = DirectXCommon::GetInstance();

	// ImGuiManagerの取得
	ImGuiManager* imgui = ImGuiManager::GetInstance();

	// --- 1.5) シーン登録 ---
	SceneManager scenes;
	scenes.Register(SceneId::TITLE, [] { return std::make_unique<TitleScene>(); });
	scenes.Register(SceneId::GAME, [] { return std::make_unique<GameScene>(); });
	scenes.SetFirst(SceneId::GAME);

	// --- 高分解能タイマ準備 ---
	LARGE_INTEGER freq{};
	::QueryPerformanceFrequency(&freq);
	LARGE_INTEGER prev{};
	::QueryPerformanceCounter(&prev);

	const float kMaxDt = 1.0f / 10.0f;

	// --- 2) メインループ ---
	while (true) {
		// エンジンの毎フレーム更新
		if (Update()) {
			break;
		}

		// dt 計測
		LARGE_INTEGER now{};
		::QueryPerformanceCounter(&now);
		double raw = static_cast<double>(now.QuadPart - prev.QuadPart) / static_cast<double>(freq.QuadPart);
		prev = now;
		float dt = static_cast<float>(raw);
		if (dt > kMaxDt)
			dt = kMaxDt;
		if (dt < 0.0f)
			dt = 0.0f;

		// --- 更新フェーズ ---
		scenes.Update(dt);

		// --- 描画フェーズ ---
		dx->PreDraw();
		scenes.Draw();
		imgui->Draw();
		dx->PostDraw();
	}

	// --- 3) 終了処理 ---
	Finalize();
	return 0;
}

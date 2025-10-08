#include "KamataEngine.h"
#include <Windows.h>

using namespace KamataEngine;

// Windowsアプリでのエントリーポイント
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int) {
	// --- 1) エンジン初期化 ---
	// タイトルは省略可。必要なら L"任意タイトル" を渡す
	Initialize(L"KamataEngine 初期化テスト");

	// DirectXCommon の取得（描画の開始/終了に使う）
	DirectXCommon* dx = DirectXCommon::GetInstance();

	// --- 2) メインループ ---
	while (true) {
		// エンジンの毎フレーム更新（true が返ったら終了要求）
		if (Update()) {
			break;
		}

		// --- 描画フェーズ（現状は空） ---
		dx->PreDraw();

		// TODO: ここにスプライトやモデルの描画を書く

		dx->PostDraw();
	}

	// --- 3) 終了処理 ---
	Finalize();

	return 0;
}

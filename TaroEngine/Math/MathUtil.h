#pragma once
#include "KamataEngine.h"

namespace MathUtil {

/// <summary>
/// 4x4 行列の乗算を行います（行メモリ配置 / 右乗算想定）。
/// </summary>
/// <param name="a">左項の行列。</param>
/// <param name="b">右項の行列。</param>
/// <returns>a と b の積行列。</returns>
static inline KamataEngine::Matrix4x4 Mul(const KamataEngine::Matrix4x4& a, const KamataEngine::Matrix4x4& b) {
	KamataEngine::Matrix4x4 c{};

	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			float s = 0.0f;
			for (int k = 0; k < 4; ++k) {
				s += a.m[i][k] * b.m[k][j];
			}
			c.m[i][j] = s;
		}
	}

	return c;
}

/// <summary>
/// 拡大・回転・平行移動を合成したアフィン変換行列を作成します。
/// </summary>
/// <param name="scale">各軸の拡大率（x, y, z）。</param>
/// <param name="rotation">各軸の回転角（ラジアン）。</param>
/// <param name="translation">各軸の平行移動量（x, y, z）。</param>
/// <returns>アフィン変換行列（4x4）。</returns>
inline KamataEngine::Matrix4x4 MakeAffineMatrix(const KamataEngine::Vector3& scale, const KamataEngine::Vector3& rotation, const KamataEngine::Vector3& translation) {
	// 各軸回転
	KamataEngine::Matrix4x4 rotX = KamataEngine::MathUtility::MakeRotateXMatrix(rotation.x);
	KamataEngine::Matrix4x4 rotY = KamataEngine::MathUtility::MakeRotateYMatrix(rotation.y);
	KamataEngine::Matrix4x4 rotZ = KamataEngine::MathUtility::MakeRotateZMatrix(rotation.z);

	// 回転合成（Z → X → Y）
	KamataEngine::Matrix4x4 rotZX = Mul(rotZ, rotX);
	KamataEngine::Matrix4x4 rot = Mul(rotZX, rotY);

	// スケール・平行移動
	KamataEngine::Matrix4x4 scaleM = KamataEngine::MathUtility::MakeScaleMatrix(scale);
	KamataEngine::Matrix4x4 transM = KamataEngine::MathUtility::MakeTranslateMatrix(translation);

	// 最終合成：S * R * T
	KamataEngine::Matrix4x4 sr = Mul(scaleM, rot);
	KamataEngine::Matrix4x4 srt = Mul(sr, transM);
	return srt;
}

} // namespace MathUtility

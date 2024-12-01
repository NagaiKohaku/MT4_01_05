#include <Novice.h>

#include "Quaternion.h"
#include "Vector3.h"

#include "cmath"

const char kWindowTitle[] = "LE2C_18_ナガイコハク_MT4_01_05_球面線形補間";

Quaternion SLerp(Quaternion q1, Quaternion q2, float t) {

	//極小の値
	float epsilon = 1e-6f;

	//q1とq2の内積
	float dot = Dot(q1, q2);

	if (dot < 0) {
		q1 = -q1; //もう片方の開店を利用する
		dot = -dot; //内積も反転
	}

	if (dot >= 1.0f - epsilon) {
		//θ=0の極限を求める
		return q1 * (1.0f - t) + q2 * t;
	}

	//なす角
	float theta = std::acosf(dot);

	//補間係数1
	float scale1 = std::sinf((1.0f - t) * theta) / std::sinf(theta);

	//補間係数2
	float scale2 = std::sinf(t * theta) / std::sinf(theta);

	//補間係数を利用して、補間後のQuaternionを求める
	return q1 * scale1 + q2 * scale2;
}

static const int kRowHeight = 20;
static const int kColumnWidth = 60;
void QuaternionScreenPrintf(int x, int y, Quaternion quaternion, const char* label) {
	Novice::ScreenPrintf(x, y, "%.02f", quaternion.x);
	Novice::ScreenPrintf(x + kColumnWidth, y, "%.02f", quaternion.y);
	Novice::ScreenPrintf(x + kColumnWidth * 2, y, "%.02f", quaternion.z);
	Novice::ScreenPrintf(x + kColumnWidth * 3, y, "%.02f", quaternion.w);
	Novice::ScreenPrintf(x + kColumnWidth * 4, y, label);
}

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	Quaternion rotation1 = MakeRotateAxisAngleQuaternion({ 0.71f,0.71f,0.0f }, 0.3f);
	Quaternion rotation2 = { -rotation1.x,-rotation1.y,-rotation1.z,-rotation1.w };

	Quaternion interpolate1 = SLerp(rotation1, rotation2, 0.0f);
	Quaternion interpolate2 = SLerp(rotation1, rotation2, 0.3f);
	Quaternion interpolate3 = SLerp(rotation1, rotation2, 0.5f);
	Quaternion interpolate4 = SLerp(rotation1, rotation2, 0.7f);
	Quaternion interpolate5 = SLerp(rotation1, rotation2, 1.0f);

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		QuaternionScreenPrintf(0, kRowHeight * 0, interpolate1, " : interpolate1, SLerp(q1,q2,0.0f)");
		QuaternionScreenPrintf(0, kRowHeight * 1, interpolate2, " : interpolate2, SLerp(q1,q2,0.3f)");
		QuaternionScreenPrintf(0, kRowHeight * 2, interpolate3, " : interpolate3, SLerp(q1,q2,0.5f)");
		QuaternionScreenPrintf(0, kRowHeight * 3, interpolate4, " : interpolate4, SLerp(q1,q2,0.7f)");
		QuaternionScreenPrintf(0, kRowHeight * 4, interpolate5, " : interpolate5, SLerp(q1,q2,1.0f)");

		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}

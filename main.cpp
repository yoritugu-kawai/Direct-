#include "class/WindowsClass.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	WinApp* winApp_ = new WinApp;

	const int32_t kClientWidth = 1280;
	const int32_t kClientHeight = 720;

	winApp_->Initialize(kClientWidth, kClientHeight);

	//　メインループ
	MSG msg{};
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else {
			//　ゲーム処理
		}
	}

	return 0;
}


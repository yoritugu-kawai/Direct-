#include "class/WinApp.h"

const wchar_t Title[] = { L"CG2WindowClass" };


int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	WinApp* windowsClass_ = new WinApp;

	const int32_t kClientWidth = 1280;
	const int32_t kClientHeight = 720;

	windowsClass_->Initialize(Title, kClientWidth, kClientHeight);

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

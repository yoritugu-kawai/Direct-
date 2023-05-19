#include "class/WinApp.h"
#include"class/DixApp.h"
const wchar_t Title[] = { L"CG2WindowClass" };


int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	WinApp* winApp_ = new WinApp;
	DixApp* dixApp_ = new DixApp;
	const int32_t kClientWidth = 1280;
	const int32_t kClientHeight = 720;
	
	winApp_->Initialize(Title, kClientWidth, kClientHeight);
	dixApp_->Initialize(kClientWidth, kClientHeight);
	dixApp_->Ma();
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
	dixApp_->Debug();
	return 0;
}

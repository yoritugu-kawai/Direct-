#include"DKJEN/Base/DxCommon.h"
#include"DKJEN/Base/WinApp.h"
const wchar_t Title[] = { L"CG2WindowClass" };


int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	const int32_t kClientWidth = 1280;
	const int32_t kClientHeight = 720;
	WinApp* winApp_ = new WinApp;
	DxCommon* dxCommon_ = new DxCommon;


	winApp_->Initialize(Title, kClientWidth, kClientHeight);
	dxCommon_->Initialize(winApp_->Width(), winApp_->Height(),winApp_->GetHwnd());
	
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
			dxCommon_->BeginFrame();
			dxCommon_->EndFrame();
		}
	}
	
	winApp_->Release();
	dxCommon_->Release(winApp_->GetHwnd());

	delete dxCommon_;
	delete winApp_;
	return 0;
}

#include"DKJEN/Base/DxCommon.h"
#include"DKJEN/Base/WinApp.h"
const wchar_t Title[] = { L"CG2WindowClass" };


int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	const int32_t kClientWidth = 1280;
	const int32_t kClientHeight = 720;
	WinApp* winApp_ = new WinApp(Title, kClientWidth, kClientHeight);
	DxCommon* dxCommon_ = new DxCommon();


	winApp_->Initialize();
	dxCommon_->Initialize(winApp_->Width(),winApp_->Height(),winApp_->Gethwnd());
	
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
	
	winApp_->Release();
	dxCommon_->Release(winApp_->Gethwnd());

	delete dxCommon_;
	delete winApp_;
	return 0;
}

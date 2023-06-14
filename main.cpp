#include"Myclass/WinApp.h"
#include"Myclass/DixApp.h"
#include"Myclass/Polygon.h"
const wchar_t Title[] = { L"CG2WindowClass" };


int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	const int32_t kClientWidth = 1280;
	const int32_t kClientHeight = 720;
	WinApp* winApp_ = new WinApp(Title, kClientWidth, kClientHeight);
	DixApp* dixApp_ = new DixApp;
	/*PolygonApp* polygon_ = new PolygonApp;*/
	
	winApp_->Initialize();

	dixApp_->Initialize(winApp_->Width(), winApp_->Height(), winApp_->Gethwnd());



	/*polygon_->Initialize(winApp_->Width(), winApp_->Height(),dixApp_->device);
	polygon_->DrawCall();*/
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
		/*	polygon_->Triangle(50, 50, 100, 100);*/
		}
	}
	dixApp_->Release(winApp_->Gethwnd());
	winApp_->Release();
	/*polygon_->Release();*/
	/*delete polygon_;*/
	delete dixApp_;
	delete winApp_;
	return 0;
}

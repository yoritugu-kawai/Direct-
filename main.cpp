#include"Myclass/WinApp.h"
#include"Myclass/Dxcommen.h"
#include"Myclass/Polygon.h"
const wchar_t Title[] = { L"CG2WindowClass" };
struct TrianglePeropety
{
	Vector4 lefe;
	Vector4  top;
	Vector4 right;
};

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	const int32_t kClientWidth = 1280;
	const int32_t kClientHeight = 720;
	
	WinApp* winApp_ = new WinApp(Title, kClientWidth, kClientHeight);
	DxCommen* dxCommen_ = new DxCommen;
	PolygonApp* polygon_ = new PolygonApp;

	winApp_->Initialize();
	dxCommen_->Initialize(winApp_->Width(), winApp_->Height(), winApp_->Gethwnd());
	//polygon_->Initialize(winApp_->Width(), winApp_->Height(), dxCommen_->deviceGet(), dxCommen_->hrGet());

	TrianglePeropety riangle[10];
	riangle[0]=
	{
		{-0.8f,-0.0f,0.0f,1.0f},
		{-0.65f,0.5f,0.0f,1.0f},
		{-0.5f,-0.0f,0.0f,1.0f}


	};
	riangle[1] =
	{
		{-0.2f,-0.0f,0.0f,1.0f},
		{0.1f,0.5f,0.0f,1.0f},
		{-0.2f,-0.0f,0.0f,1.0f}


	};

	
	//　メインループ
	MSG msg{};
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else {
			dxCommen_->BeginFrame();
			for (int i = 0; i < 2; i++) {
				polygon_->Triangle(riangle[i].lefe, riangle[i].top, riangle[i].right, dxCommen_->commandListGet(), dxCommen_->rootSignatureGet(), dxCommen_->graphicsPipelineStateGet());
			}
		
			
			dxCommen_->EndFrame();
			//　ゲーム処理

		}
	}

	winApp_->Release();
	dxCommen_->Release(winApp_->Gethwnd());
	polygon_->Release(dxCommen_->rootSignatureGet(), dxCommen_->graphicsPipelineStateGet(), dxCommen_->pixelShaderBlobGet(), dxCommen_->vertexShaderBlobGet(),
		dxCommen_->signatureBlobGet(), dxCommen_->errorBlobGet());
	delete polygon_;
	delete dxCommen_;
	delete winApp_;
	return 0;
}

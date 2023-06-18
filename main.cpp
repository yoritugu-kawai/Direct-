#include"Myclass/WinApp.h"
#include"Myclass/Dxcommen.h"
#include"Myclass/Polygon.h"
const wchar_t Title[] = { L"CG2WindowClass" };




struct TrianglePropaty
{
	Vector4 lefe;
	Vector4  top;
	Vector4 right;
	BufferResource Resource;

};

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	const int32_t kClientWidth = 1280;
	const int32_t kClientHeight = 720;
	
	WinApp* winApp_ = new WinApp(Title, kClientWidth, kClientHeight);
	DxCommen* dxCommen_ = new DxCommen;
	PolygonApp* polygon_ = new PolygonApp;

	winApp_->Initialize();
	dxCommen_->Initialize(winApp_->Width(), winApp_->Height(), winApp_->Gethwnd());
	


	
	TrianglePropaty triangle[10];
	

	//for () {
	//
	//	triangle[i]->Init(TriaglePropaty[i]);
	//}
	
	triangle[0]=
	{
		{-0.8f,-0.0f,0.0f,1.0f},
		{-0.65f,0.5f,0.0f,1.0f},
		{-0.5f,-0.0f,0.0f,1.0f},
		{polygon_->CreateBufferResource(dxCommen_->deviceGet())}


	};
	triangle[1] =
	{
		{-0.4f,-0.0f,0.0f,1.0f},
		{-0.35f,0.5f,0.0f,1.0f},
		{-0.2f,-0.0f,0.0f,1.0f},
		{ polygon_->CreateBufferResource(dxCommen_->deviceGet()) }


	};

	triangle[2] =
	{
		{-0.1f,-0.0f,0.0f,1.0f},
		{0.1f,0.5f,0.0f,1.0f},
		{0.2f,-0.0f,0.0f,1.0f},
		{ polygon_->CreateBufferResource(dxCommen_->deviceGet()) }


	};
	triangle[3] =
	{
		{-0.1f,-0.3f,0.0f,1.0f},
		{0.1f,-0.1f,0.0f,1.0f},
		{0.2f,-0.3f,0.0f,1.0f},
		{ polygon_->CreateBufferResource(dxCommen_->deviceGet()) }


	};
	triangle[4] =
	{
		{-0.8f,-0.3f,0.0f,1.0f},
		{-0.65f,-0.1f,0.0f,1.0f},
		{-0.5f,-0.3f,0.0f,1.0f},
		{polygon_->CreateBufferResource(dxCommen_->deviceGet())}


	};
	triangle[5] =
	{
		{-0.4f,-0.3f,0.0f,1.0f},
		{-0.35f,-0.1f,0.0f,1.0f},
		{-0.2f,-0.3f,0.0f,1.0f},
		{ polygon_->CreateBufferResource(dxCommen_->deviceGet()) }


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
			polygon_->Initialize(winApp_->Width(), winApp_->Height(), dxCommen_->commandListGet());




			//描画処理
			/*for () {
				triagnle[i]->Draw();


			}*/



			for (int i = 0; i < 6; i++) {
				polygon_->Draw(triangle[i].lefe, triangle[i].top, triangle[i].right, dxCommen_->commandListGet(),
					dxCommen_->rootSignatureGet(), dxCommen_->graphicsPipelineStateGet(),
					triangle[i].Resource.vertexResource, triangle[i].Resource);
			}
		
			
			dxCommen_->EndFrame();
			//　ゲーム処理

		}
	}

	winApp_->Release();
	dxCommen_->Release(winApp_->Gethwnd());

		polygon_->Release(dxCommen_->rootSignatureGet(), dxCommen_->graphicsPipelineStateGet(), dxCommen_->pixelShaderBlobGet(), dxCommen_->vertexShaderBlobGet(),
			dxCommen_->signatureBlobGet(), dxCommen_->errorBlobGet(), triangle[0].Resource.vertexResource);
	
	delete polygon_;

	delete dxCommen_;
	delete winApp_;
	return 0;
}

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
	winApp_->Initialize();
	DxCommon* dxCommon_ = new DxCommon;
	dxCommon_->Initialize(winApp_->Width(), winApp_->Height(), winApp_->Gethwnd());
	const int max = 6;
	PolygoType* polygon_[max]{};
	for (int i = 0; i < max; i++) {
		polygon_[i] = new PolygoType;
		polygon_[i]->Initiluze(dxCommon_);
	}

	TrianglePropaty triangle[max];

	triangle[0] =
	{

		{-0.8f,-0.0f,0.0f,1.0f},
		{-0.65f,0.5f,0.0f,1.0f},
		{-0.5f,-0.0f,0.0f,1.0f},
		{polygon_[0]->CreateBufferResource()}


	};

	triangle[1] =
	{
		{-0.4f,-0.0f,0.0f,1.0f},
		{-0.35f,0.5f,0.0f,1.0f},
		{-0.2f,-0.0f,0.0f,1.0f},
		{ polygon_[1]->CreateBufferResource()}


	};

	triangle[2] =
	{
		{-0.1f,-0.0f,0.0f,1.0f},
		{0.1f,0.5f,0.0f,1.0f},
		{0.2f,-0.0f,0.0f,1.0f},
		{ polygon_[2]->CreateBufferResource()}


	};
	triangle[3] =
	{
		{-0.1f,-0.3f,0.0f,1.0f},
		{0.1f,-0.1f,0.0f,1.0f},
		{0.2f,-0.3f,0.0f,1.0f},
		{ polygon_[3]->CreateBufferResource()}


	};
	triangle[4] =
	{
		{-0.8f,-0.3f,0.0f,1.0f},
		{-0.65f,-0.1f,0.0f,1.0f},
		{-0.5f,-0.3f,0.0f,1.0f},
		{polygon_[4]->CreateBufferResource()}


	};
	triangle[5] =
	{
		{-0.4f,-0.3f,0.0f,1.0f},
		{-0.35f,-0.1f,0.0f,1.0f},
		{-0.2f,-0.3f,0.0f,1.0f},
		{ polygon_[5]->CreateBufferResource()}


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
			dxCommon_->BeginFrame();

			//更新処理
			for (int i = 0; i < max; i++) {

				polygon_[i]->Update(winApp_->Width(), winApp_->Height());
			}

			//描画処理
			for (int i = 0; i < max; i++) {
				polygon_[i]->Draw(triangle[i].lefe, triangle[i].top, triangle[i].right,
					triangle[i].Resource.vertexResource, triangle[i].Resource);
			}


			dxCommon_->EndFrame();
			//　ゲーム処理

		}
	}

	winApp_->Release();
	dxCommon_->Release(winApp_->Gethwnd());


	for (int i = 0; i < max; i++) {
		delete polygon_[i];
	}
	delete dxCommon_;
	delete winApp_;
	return 0;
}

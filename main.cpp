#include"Myclass/dase/WinApp.h"
#include"Myclass/dase/Dxcommen.h"
#include"Myclass/type/Polygon.h"

const wchar_t Title[] = { L"CG2WindowClass" };

struct TrianglePropaty
{
	Vector4 left;
	Vector4  top;
	Vector4 right;
	unsigned int color;

};

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	const int32_t kClientWidth = 1280;
	const int32_t kClientHeight = 720;

	WinApp* winApp_ = new WinApp(Title, kClientWidth, kClientHeight);
	winApp_->Initialize();
	DxCommon* dxCommon_ = new DxCommon;
	dxCommon_->Initialize(winApp_->Width(), winApp_->Height(), winApp_->Gethwnd());

	const int triangleCount = 6;
	
	TrianglePropaty triangle[triangleCount];

	triangle[0] =
	{
	    {-0.8f,-0.0f,0.0f,1.0f},
	    {-0.6f,0.5f,0.0f,1.0f},
		{-0.5f,-0.0f,0.0f,1.0f},
		{0x783964ff}
	};

	triangle[1] =
	{
		{-0.4f,-0.0f,0.0f,1.0f},
		{-0.35f,0.5f,0.0f,1.0f},
		{-0.2f,-0.0f,0.0f,1.0f},
	    {0xff44ffff}
	};

	triangle[2] =
	{
		{-0.1f,-0.0f,0.0f,1.0f},
		{0.1f,0.5f,0.0f,1.0f},
		{0.2f,-0.0f,0.0f,1.0f},
		{0x22ffffff}
	};

	triangle[3] =
	{
		{-0.1f,-0.3f,0.0f,1.0f},
		{0.1f,-0.1f,0.0f,1.0f},
		{0.2f,-0.3f,0.0f,1.0f},
		{0xff00ffff}
	};

	triangle[4] =
	{
		{-0.8f,-0.3f,0.0f,1.0f},
		{-0.65f,-0.1f,0.0f,1.0f},
		{-0.5f,-0.3f,0.0f,1.0f},
		{0xffffafaf}

	};

	triangle[5] =
	{
		{-0.4f,-0.3f,0.0f,1.0f},
		{-0.35f,-0.1f,0.0f,1.0f},
		{-0.2f,-0.3f,0.0f,1.0f},
		{0xffffffff}
	};

	PolygoType* polygon_[triangleCount]{};
	for (int i = 0; i < triangleCount; i++) {
		polygon_[i] = new PolygoType;
		polygon_[i]->Initiluze(dxCommon_);
	}

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
			

			//描画処理
			for (int i = 0; i < triangleCount; i++) {
				polygon_[i]->Draw(triangle[i].left, triangle[i].top, triangle[i].right, triangle[i].color);
			}

			dxCommon_->EndFrame();
			//　ゲーム処理

		}
	}

	winApp_->Release();
	dxCommon_->Release(winApp_->Gethwnd());

	for (int i = 0; i < triangleCount; i++) {
		delete polygon_[i];
	}
	delete dxCommon_;
	delete winApp_;
	return 0;
}

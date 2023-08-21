#include"Myclass/dase/WinApp.h"
#include"Myclass/dase/Dxcommen.h"
#include"Myclass/type/Polygon.h"
#include"Myclass/type/ImguiManager.h"
#include"Myclass/type/Texture.h"
const wchar_t Title[] = { L"CG2WindowClass" };

struct TrianglePropaty
{
	Vector4 lefe;
	Vector4  top;
	Vector4 right;
	Vector4 color;

};


int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	const int32_t kClientWidth = 1280;
	const int32_t kClientHeight = 720;
	//ウインドウズ
	WinApp* winApp_ = new WinApp(Title, kClientWidth, kClientHeight);
	winApp_->Initialize();
	//DX
	DxCommon* dxCommon_ = new DxCommon;
	dxCommon_->Initialize(winApp_->Width(), winApp_->Height(), winApp_->Gethwnd());
	//IG
	ImguiManager* imguiManager = new ImguiManager;
	imguiManager->Initialize(winApp_->Gethwnd(),dxCommon_->deviceGet(),dxCommon_->swapChainDescGet(),dxCommon_->rtvDescGet(),dxCommon_->srvDescriptorHeapGet());
	const int triangleCount = 6;
	//テキスト
	Texture* tex_ = new Texture;
	tex_->Initiluze(dxCommon_);

	TexProeerty  tex;
	tex = tex_->Load();


	//三角形
	TrianglePropaty triangle[triangleCount];
	triangle[0] =
	{
		{-0.5f,-0.5f,0.0f,1.0f},
		{-0.0f,0.5f,0.0f,1.0f},
		{0.5f,-0.5f,0.0f,1.0f},
		{1.0f,0.0f,0.0f,1.0f}

	};

	//triangle[0] =
	//{

	//    {-0.8f,-0.0f,0.0f,1.0f},
	//    {-0.6f,0.5f,0.0f,1.0f},
	//	{-0.5f,-0.0f,0.0f,1.0f},
	//    {1.0f,0.0f,0.0f,1.0f}


	//};

	triangle[1] =
	{
		{-0.4f,-0.0f,0.0f,1.0f},
		{-0.35f,0.5f,0.0f,1.0f},
		{-0.2f,-0.0f,0.0f,1.0f},
		{1.0f,0.0f,1.0f,1.0f}


	};

	//triangle[2] =
	//{
	//	{-0.1f,-0.0f,0.0f,1.0f},
	//	{0.1f,0.5f,0.0f,1.0f},
	//	{0.2f,-0.0f,0.0f,1.0f},
	//	{1.0f,0.0f,0.0f,0.0f}


	//};
	//triangle[3] =
	//{
	//	{-0.1f,-0.3f,0.0f,1.0f},
	//	{0.1f,-0.1f,0.0f,1.0f},
	//	{0.2f,-0.3f,0.0f,1.0f},
	//	{1.0f,0.0f,0.5f,1.0f}


	//};
	//triangle[4] =
	//{
	//	{-0.8f,-0.3f,0.0f,1.0f},
	//	{-0.65f,-0.1f,0.0f,1.0f},
	//	{-0.5f,-0.3f,0.0f,1.0f},
	//    {0.2f,0.0f,0.0f,1.0f}

	//};
	//triangle[5] =
	//{
	//	{-0.4f,-0.3f,0.0f,1.0f},
	//	{-0.35f,-0.1f,0.0f,1.0f},
	//	{-0.2f,-0.3f,0.0f,1.0f},
	//	{0.0f,0.0f,0.0f,0.0f}
	//};
	 
	PolygoType* polygon_[triangleCount]{};
	for (int i = 0; i < triangleCount; i++) {
		polygon_[i] = new PolygoType;
		polygon_[i]->Initiluze(dxCommon_, winApp_->Width(), winApp_->Height(), triangle[i].lefe, triangle[i].top, triangle[i].right);

	}
	Matrix4x4 matrix[triangleCount];
	Vector3 scale[triangleCount];
	Vector3 rotate[triangleCount];
	Vector3 translate[triangleCount];
	for (int i = 0; i < triangleCount; i++) {
		matrix[i] = MakeIdentity4x4();
		scale[i] = {1,1,1};
		rotate[i] = { 0,0,0 };
		translate[i] = { 0,0,0 };

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
			imguiManager->BeginFrame(dxCommon_->srvDescriptorHeapGet(),dxCommon_->commandListGet());
			//更新処理
			
			/******************************************************/
				ImGui::Begin("Triangle1");
				ImGui::ColorEdit3("color", (float*)&triangle[0].color);
				ImGui::SliderFloat3("scale", &scale[0].x, -0.0f, 5.0f);
				ImGui::SliderFloat3("rotate", &rotate[0].x, -1.0f, 1.0f);
				ImGui::SliderFloat3("translate", &translate[0].x, -1.0f, 1.0f);
				ImGui::End();

				ImGui::Begin("Triangle2");
				ImGui::ColorEdit3("color", (float*)&triangle[1].color);
				ImGui::SliderFloat3("scale", &scale[1].x, -0.0f, 5.0f);
				ImGui::SliderFloat3("rotate", &rotate[1].x, -1.0f, 1.0f);
				ImGui::SliderFloat3("translate", &translate[1].x, -1.0f, 1.0f);
				ImGui::End();
			
			//
			//描画処理
			for (int i = 0; i < triangleCount; i++) {
				matrix[i] = MakeAffineMatrix(scale[i], rotate[i],translate[i]);
				polygon_[i]->Draw(triangle[i].color,matrix[i],tex);


			}
			imguiManager->EndFrame(dxCommon_->commandListGet());
			dxCommon_->EndFrame();
			//　ゲーム処理

		}
	}
	tex_->End();
	winApp_->Release();
	dxCommon_->Release(winApp_->Gethwnd());


	for (int i = 0; i < triangleCount; i++) {
		delete polygon_[i];
	}
	delete dxCommon_;
	delete winApp_;
	return 0;
}


#include"DKJEN/Base/DxCommon.h"
#include"DKJEN/Base/WinApp.h"
#include "DKJEN/Shader/CompileShader.h"
#include"DKJEN/Base/PipelineState.h"
#include"DKJEN/Type/Polygon.h"
const wchar_t Title[] = { L"CG2WindowClass" };



int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	
	WinApp::Initialize(Title);
	DxCommon::Initialize();
	CompileShader::DXC();
	CompileShader::ShaderCompile();
	PipelineState::CreatePSO();
	PolygonType* polygon_[2] ;
	polygon_[0] = new PolygonType;
	polygon_[1] = new PolygonType;
	polygon_[0]->Initialize({ 0.5f,0.0f,0.0f,1.0f }, { 1.0f,1.0f,1.0f,1.0f });
	polygon_[1]->Initialize({0.0f,0.0f,0.0f,1.0f}, {1.0f,1.0f,0.0f,0.0f});
	//DxCommon* dxCommon_ = new DxCommon;


	
	//dxCommon_->Initialize(winApp_->Width(), winApp_->Height(),winApp_->GetHwnd());
	
	//　メインループ
	MSG msg{};
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		DxCommon::BeginFrame();
			//　ゲーム処理
			//　ゲーム処理
		polygon_[0]->Draw();
		polygon_[1]->Draw();
		DxCommon::EndFrame();
		
	}
	polygon_[0]->Release();
	polygon_[1]->Release();
	CompileShader::Release();

	PipelineState::Release();
	DxCommon::Release();

	
	
	return 0;
}

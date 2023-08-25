#include"DKJEN/Base/DxCommon.h"
#include"DKJEN/Base/WinApp.h"
#include "DKJEN/Shader/CompileShader.h"
#include"DKJEN/Base/PipelineState.h"
const wchar_t Title[] = { L"CG2WindowClass" };


int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	
	WinApp::Initialize(Title);
	DxCommon::Initialize();
	CompileShader::DXC();
	CompileShader::ShaderCompile();
	PipelineState::CreatePSO();
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

		DxCommon::EndFrame();
		
	}
	
	CompileShader::Release();

	PipelineState::Release();
	DxCommon::Release();

	
	
	return 0;
}

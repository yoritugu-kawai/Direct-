#include"DKJEN/Base/DxCommon.h"
#include"DKJEN/Base/WinApp.h"
#include "DKJEN/Shader/CompileShader.h"
#include"DKJEN/Base/PipelineState.h"
#include"DKJEN/Type/Polygon.h"
#include"DKJEN/Type/Texture.h"
#include"DKJEN/Imgui/imguiManager.h"
const wchar_t Title[] = { L"CG2WindowClass" };



int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	WinApp::Initialize(Title);
	DxCommon::Initialize();
	CompileShader::DXC();
	CompileShader::ShaderCompile();
	PipelineState::CreatePSO();

	ImguiManager* imguiManager = new ImguiManager;
	imguiManager->Initialize();



	PolygonType* polygon_[2];
	polygon_[0] = new PolygonType;
	polygon_[1] = new PolygonType;

	polygon_[0]->Initialize({ 0.5f,0.0f,0.0f,1.0f }, { 1.0f,1.0f,1.0f,1.0f });
	polygon_[1]->Initialize({ 0.0f,0.0f,0.0f,1.0f }, { 1.0f,1.0f,0.0f,0.0f });

	//テキスト
	Texture* tex_ = new Texture;
	tex_->Initiluze();

	TexProeerty  tex;
	tex = tex_->Load();
	

	Matrix4x4 matrix[2];
	Vector3 scale[2];
	Vector3 rotate[2];
	Vector3 translate[2];
	Vector4 color[2];


	for (int i = 0; i <2 ; i++) {
		matrix[i] = MakeIdentity4x4();
		scale[i] = { 1,1,1 };
		rotate[i] = { 0,0,0 };
		translate[i] = { 0,0,0 };
		color[i] = { 1.0f,1.0f,0.0f,0.0f };

	}
	//　メインループ
	MSG msg{};
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		DxCommon::BeginFrame();
		imguiManager->BeginFrame();
		//　ゲーム処理
		//　ゲーム処理


		ImGui::Begin("Triangle1");
		ImGui::ColorEdit3("color", (float*)&color);
		ImGui::SliderFloat3("scale", &scale[0].x, -0.0f, 5.0f);
		ImGui::SliderFloat3("rotate", &rotate[0].x, -1.0f, 1.0f);
		ImGui::SliderFloat3("translate", &translate[0].x, -1.0f, 1.0f);
		ImGui::End();

		ImGui::Begin("Triangle2");
		ImGui::ColorEdit3("color", (float*)&color);
		ImGui::SliderFloat3("scale", &scale[1].x, -0.0f, 5.0f);
		ImGui::SliderFloat3("rotate", &rotate[1].x, -1.0f, 1.0f);
		ImGui::SliderFloat3("translate", &translate[1].x, -1.0f, 1.0f);
		ImGui::End();
		polygon_[0]->Draw(tex);
		//polygon_[1]->Draw(tex);
		///
		imguiManager->EndFrame();
		DxCommon::EndFrame();

	}
	polygon_[0]->Release();
	//polygon_[1]->Release();
	CompileShader::Release();
	imguiManager->Release();
	tex.Resource->Release();
	PipelineState::Release();
	DxCommon::Release();



	return 0;
}

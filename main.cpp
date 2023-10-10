#include"DKJEN/Base/DxCommon.h"
#include"DKJEN/Base/WinApp.h"
#include "DKJEN/Shader/CompileShader.h"
#include"DKJEN/Base/PipelineState.h"
#include"DKJEN/Type/Polygon.h"
#include"DKJEN/Type/Texture.h"
#include"DKJEN/Imgui/imguiManager.h"
#include"DKJEN/Type/Sprite.h"


const wchar_t Title[] = { L"ド根性エンジン" };


struct TrianglePropaty
{
	Vector4 lefe;
	Vector4  top;
	Vector4 right;
	Vector4 color;

};

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	WinApp::Initialize(Title);
	DxCommon::Initialize();
	CompileShader::DXC();
	CompileShader::ShaderCompile();
	PipelineState::CreatePSO();

	ImguiManager* imguiManager = new ImguiManager;
	imguiManager->Initialize();

	//スプライト
	Sprite* SpriteTex = new Sprite;
	SpriteTex->Initialize();

	
	//テキスト
	Texture* tex_ = new Texture;
	tex_->Initiluze();

	TexProeerty  tex;
	tex = tex_->Load();
	///座標
	const int triangleCount = 2;


	TrianglePropaty triangle[triangleCount];
	triangle[0] =
	{
		{-0.5f,-0.5f,0.0f,1.0f},
		{0.0f,0.5f,0.0f,1.0f},
		{0.5f,-0.5f,0.0f,1.0f},
		{1.0f,1.0f,1.0f,1.0f}

	};

	triangle[1] =
	{

		{-0.5f,-0.5f,0.0f,1.0f},
		{0.0f,0.5f,0.0f,1.0f},
		{0.5f,-0.5f,0.0f,1.0f},
		{1.0f,0.0f,0.0f,1.0f}

	};
	float Speed =0.03f;
	//imgui
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
		color[i] = { 1.0f,1.0f,1.0f,1.0f };

	}

		PolygonType* polygon_[triangleCount];
	for (int i = 0; i < triangleCount; i++) {
		polygon_[i] = new PolygonType;
		polygon_[i]->Initialize(triangle[i].lefe, triangle[i].top, triangle[i].right);
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
		ImGui::ColorEdit3("color", (float*)&color[0]);
		ImGui::SliderFloat3("scale", &scale[0].x, -0.0f, 5.0f);
		ImGui::SliderFloat3("rotate", &rotate[0].x, -5.0f, 5.0f);
		ImGui::SliderFloat3("translate", &translate[0].x, -5.0f, 5.0f);
		
		ImGui::End();

		ImGui::Begin("Triangle2");
		ImGui::ColorEdit3("color", (float*)&color[1]);
		ImGui::SliderFloat3("scale", &scale[1].x, -5.0f, 5.0f);
		ImGui::SliderFloat3("rotate", &rotate[1].x, -5.0f, 5.0f);
		ImGui::SliderFloat3("translate", &translate[1].x, -5.0f, 5.0f);
		ImGui::End();
		for (int i = 0; i < triangleCount; i++) {
			matrix[i] = MakeAffineMatrix(scale[i], rotate[i], translate[i]);
			polygon_[i]->Draw(tex, matrix[i], color[i]);
		
		
		}
		SpriteTex->Darw();


		///
		imguiManager->EndFrame();
		DxCommon::EndFrame();

	}
	for (int i = 0; i < triangleCount; i++) {
		polygon_[i]->Release();
	}
	
	CompileShader::Release();
	imguiManager->Release();
	tex.Resource->Release();
	SpriteTex->Release();
	PipelineState::Release();
	DxCommon::Release();


	return 0;
}

#include"DKJEN/Base/DxCommon.h"
#include"DKJEN/Base/WinApp.h"
#include"DKJEN/Base/TexturePSO.h"
#include"DKJEN/Base/PolygonPSO.h"
#include"DKJEN/Base/SpritePSO.h"

#include"DKJEN/Shader/TextureCompileShader.h"
#include"DKJEN/Shader/PolygonCompileShader.h"
#include"DKJEN/Shader/SpriteCompileShader.h"


#include"DKJEN/Imgui/imguiManager.h"

#include"DKJEN/Type/Polygon.h"
#include"DKJEN/Type/Sprite.h"
#include"DKJEN/Type/Texture.h"

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
	TextureCompileShader::DXC();
	PolygonCompileShader::DXC();
	SpriteCompileShader::DXC();

	TextureCompileShader::ShaderCompile();
	PolygonCompileShader::ShaderCompile();
	SpriteCompileShader::ShaderCompile();

	TexturePSO::CreatePSO();
	PolygonPSO::CreatePSO();
	SpritePSO::CreatePSO();

	ImguiManager* imguiManager = new ImguiManager;
	imguiManager->Initialize();

	//スプライト
	Sprite* SpriteTex = new Sprite;
	SpriteTex->Initialize();



	///座標
	const int Count = 2;


	TrianglePropaty triangleTextur[Count];
	triangleTextur[0] =
	{
		{-0.5f,-0.5f,0.0f,1.0f},
		{0.0f,0.5f,0.0f,1.0f},
		{0.5f,-0.5f,0.0f,1.0f},
		{1.0f,1.0f,1.0f,1.0f}

	};

	triangleTextur[1] =
	{

		{-0.5f,-0.5f,0.0f,1.0f},
		{0.0f,0.5f,0.0f,1.0f},
		{0.5f,-0.5f,0.0f,1.0f},
		{1.0f,0.0f,0.0f,1.0f}

	};


	TrianglePropaty triangle[Count];
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

	//imgui
	ImGguiTransfrom imGuiTextur[2];


	for (int i = 0; i < 2; i++) {
		imGuiTextur[i].matrix = MakeIdentity4x4();
		imGuiTextur[i].scale = { 1,1,1 };
		imGuiTextur[i].rotate = { 0,0,0 };
		imGuiTextur[i].translate = { 0,0,0 };
		imGuiTextur[i].color = { 1.0f,1.0f,1.0f,1.0f };

	}

	ImGguiTransfrom imGuiPolygon[2];


	for (int i = 0; i < 2; i++) {
		imGuiPolygon[i].matrix = MakeIdentity4x4();
		imGuiPolygon[i].scale = { 1,1,1 };
		imGuiPolygon[i].rotate = { 0,0,0 };
		imGuiPolygon[i].translate = { 0,0,0 };
		imGuiPolygon[i].color = { 1.0f,1.0f,1.0f,1.0f };

	}

	PolygonType* polygon_[Count];
	for (int i = 0; i < Count; i++) {
		polygon_[i] = new PolygonType;
		polygon_[i]->Initialize(triangleTextur[i].lefe, triangleTextur[i].top, triangleTextur[i].right);
	}

	Texture* texture_[Count];
	for (int i = 0; i < Count; i++) {
		texture_[i] = new Texture;
		texture_[i]->Initialize(triangle[i].lefe, triangle[i].top, triangle[i].right);
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


		//ImGui::Begin("Texture1");
		//ImGui::ColorEdit3("color", (float*)&imGuiTextur[0].color);
		//ImGui::SliderFloat3("scale", &imGuiTextur[0].scale.x, -0.0f, 5.0f);
		//ImGui::SliderFloat3("rotate", &imGuiTextur[0].rotate.x, -5.0f, 5.0f);
		//ImGui::SliderFloat3("translate", &imGuiTextur[0].translate.x, -5.0f, 5.0f);
		//ImGui::End();

		//ImGui::Begin("Texture2");
		//ImGui::ColorEdit3("color", (float*)&imGuiTextur[1].color);
		//ImGui::SliderFloat3("scale", &imGuiTextur[1].scale.x, -0.0f, 5.0f);
		//ImGui::SliderFloat3("rotate", &imGuiTextur[1].rotate.x, -5.0f, 5.0f);
		//ImGui::SliderFloat3("translate", &imGuiTextur[1].translate.x, -5.0f, 5.0f);
		//ImGui::End();

		//for (int i = 0; i < Count; i++) {
		//	imGuiTextur[i].matrix = MakeAffineMatrix(imGuiTextur[i].scale, imGuiTextur[i].rotate, imGuiTextur[i].translate);
		//	texture_[i]->Draw(imGuiTextur[i].matrix, imGuiTextur[i].color);


		//}

		//ImGui::Begin("polygon1");
		//ImGui::ColorEdit3("color", (float*)&imGuiPolygon[0].color);
		//ImGui::SliderFloat3("scale", &imGuiPolygon[0].scale.x, -0.0f, 5.0f);
		//ImGui::SliderFloat3("rotate", &imGuiPolygon[0].rotate.x, -5.0f, 5.0f);
		//ImGui::SliderFloat3("translate", &imGuiPolygon[0].translate.x, -5.0f, 5.0f);
		//ImGui::End();

		//ImGui::Begin("polygon2");
		//ImGui::ColorEdit3("color", (float*)&imGuiPolygon[1].color);
		//ImGui::SliderFloat3("scale", &imGuiPolygon[1].scale.x, -0.0f, 5.0f);
		//ImGui::SliderFloat3("rotate", &imGuiPolygon[1].rotate.x, -5.0f, 5.0f);
		//ImGui::SliderFloat3("translate", &imGuiPolygon[1].translate.x, -5.0f, 5.0f);
		//ImGui::End();


		//for (int i = 0; i < Count; i++) {
		//	imGuiPolygon[i].matrix = MakeAffineMatrix(imGuiPolygon[i].scale, imGuiPolygon[i].rotate, imGuiPolygon[i].translate);
		//	polygon_[i]->Draw(imGuiPolygon[i].matrix, imGuiPolygon[i].color);


		//}

		SpriteTex->Darw();


		imguiManager->EndFrame();
		DxCommon::EndFrame();

	}

	/*
	*************************
	*********   解放  *******
	*************************
	*/
	for (int i = 0; i < Count; i++) {
		texture_[i]->Release();
	}
	for (int i = 0; i < Count; i++) {
		polygon_[i]->Release();
	}
	TextureCompileShader::Release();
	PolygonCompileShader::Release();
	SpriteCompileShader::Release();

	TexturePSO::Release();
	PolygonPSO::Release();
	SpritePSO::Release();


	imguiManager->Release();
	SpriteTex->Release();
	DxCommon::Release();


	return 0;
}

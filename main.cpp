#include"DKJEN/Base/DxCommon.h"
#include"DKJEN/Base/WinApp.h"
#include"DKJEN/Base/ImageLoading.h"

#include"DKJEN/Math/Math.h"
#include"DKJEN/Imgui/imguiManager.h"

#include"DKJEN/Type/Polygon.h"
#include"DKJEN/Type/Sprite.h"
#include"DKJEN/Type/Texture.h"
#include"DKJEN/Type/Sphere.h"
#include"DKJEN/Type/Obj3D.h"
#include"DKJEN/Utilipy/rektyk.h"
#include"DKJEN/Utilipy/Input.h"
const wchar_t Title[] = { L"ド根性エンジン" };


struct Transfrom4
{
	Vector4 lefe;
	Vector4  top;
	Vector4 right;
	Vector4 color;

};

static D3DResourceLeaker leaker;
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	WinApp::Initialize(Title);
	DxCommon::Initialize();
	ImguiManager::Initialize();

	TextureCompileShader::DXC();
	PolygonCompileShader::DXC();
	SpriteCompileShader::DXC();
	LightCompileShader::DXC();

	TextureCompileShader::ShaderCompile();
	PolygonCompileShader::ShaderCompile();
	SpriteCompileShader::ShaderCompile();
	LightCompileShader::ShaderCompile();

	TexturePSO::CreatePSO();
	PolygonPSO::CreatePSO();
	SpritePSO::CreatePSO();
	LightPSO::CreatePSO();
	ImageLoading* imageLoading = new ImageLoading;
	imageLoading->Initiluze();
	TexProeerty tex = imageLoading->LoadTexture("resource/e.png");
	TexProeerty tex3 = imageLoading->LoadTexture("resource/monsterBall.png");
	TexProeerty tex2 = imageLoading->LoadTexture("resource/uvChecker.png");
	//スプライト
	Input::Initialize();
	// 球
	Sphere* sphere_ = new Sphere;
	sphere_->Initialize({ 0.0f,0.0f,0.0f,1.0f }, 0.3f, tex3);
	//3Dモデル
	Obj3D* obj3D = new Obj3D;
	obj3D->Initialize(tex2);

	///座標
	const int Count = 2;


	Transfrom4 triangleTextur[Count];
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


	Transfrom4 triangle[Count];
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
	Transfrom4 SpriteTrans =
	{
		{560.f,0.0f,0.0f,1.0f},
		{ 0.0f,360.0f,0.0f,1.0f },
		{560.0f,360.0f,0.0f,1.0f}

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

	ImGguiTransfrom imGuiSphere[1];
	for (int i = 0; i < 1; i++) {
		imGuiSphere[i].matrix = MakeIdentity4x4();
		imGuiSphere[i].scale = { 1.0f, 1.0f, 1.0f };
		imGuiSphere[i].rotate = { 0.0f, 4.7f, 0.0f };
		imGuiSphere[i].translate = { 0.0f, 0.0f, 0.0f };
		imGuiSphere[i].color = { 1.0f,1.0f,1.0f,1.0f };

	}
	ImGguiTransfrom imGuiSprite;
	imGuiSprite.matrix = MakeIdentity4x4();
	imGuiSprite.scale = { 1.0f,1.0f,1.0f };
	imGuiSprite.rotate = { 0.0f,0.0f,0.0f };
	imGuiSprite.translate = { 0.0f,0.0f,0.0f };

	ImGguiTransfrom imGui3D[1];
	for (int i = 0; i < 1; i++) {
		imGui3D[i].matrix = MakeIdentity4x4();
		imGui3D[i].scale = { 0.5f, 0.5f, 0.5f };
		imGui3D[i].rotate = { 0.0f, 0.0f, 0.0f };
		imGui3D[i].translate = { 0.0f, 0.0f, 0.0f };
		imGui3D[i].color = { 1.0f,1.0f,1.0f,1.0f };

	}
	/////初期化
	PolygonType* polygon_[Count];
	for (int i = 0; i < Count; i++) {
		polygon_[i] = new PolygonType;
		polygon_[i]->Initialize(triangleTextur[i].lefe, triangleTextur[i].top, triangleTextur[i].right);
	}

	Texture* texture_[Count];
	for (int i = 0; i < Count; i++) {
		texture_[i] = new Texture;
		texture_[i]->Initialize(triangle[i].lefe, triangle[i].top, triangle[i].right, tex2);
	}

	Sprite* SpriteTex = new Sprite;
	SpriteTex->Initialize(tex, SpriteTrans.lefe, SpriteTrans.top, SpriteTrans.right);


	//　メインループ
	MSG msg{};
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		DxCommon::BeginFrame();
		ImguiManager::BeginFrame();
		Input::BeginFlame();

		//　ゲーム処理
		//　ゲーム処理


		ImGui::Begin("Texture1");
		ImGui::ColorEdit3("color", (float*)&imGuiTextur[0].color);
		ImGui::SliderFloat3("scale", &imGuiTextur[0].scale.x, -0.0f, 5.0f);
		ImGui::SliderFloat3("rotate", &imGuiTextur[0].rotate.x, -5.0f, 5.0f);
		ImGui::SliderFloat3("translate", &imGuiTextur[0].translate.x, -5.0f, 5.0f);
		ImGui::End();

		ImGui::Begin("Texture2");
		ImGui::ColorEdit3("color", (float*)&imGuiTextur[1].color);
		ImGui::SliderFloat3("scale", &imGuiTextur[1].scale.x, -0.0f, 5.0f);
		ImGui::SliderFloat3("rotate", &imGuiTextur[1].rotate.x, -5.0f, 5.0f);
		ImGui::SliderFloat3("translate", &imGuiTextur[1].translate.x, -5.0f, 5.0f);
		ImGui::End();

		for (int i = 0; i < Count; i++) {
			imGuiTextur[i].matrix = MakeAffineMatrix(imGuiTextur[i].scale, imGuiTextur[i].rotate, imGuiTextur[i].translate);
			texture_[i]->Draw(imGuiTextur[i].matrix, imGuiTextur[i].color);


		}

		/*ImGui::Begin("polygon1");
		ImGui::ColorEdit3("color", (float*)&imGuiPolygon[0].color);
		ImGui::SliderFloat3("scale", &imGuiPolygon[0].scale.x, -0.0f, 5.0f);
		ImGui::SliderFloat3("rotate", &imGuiPolygon[0].rotate.x, -5.0f, 5.0f);
		ImGui::SliderFloat3("translate", &imGuiPolygon[0].translate.x, -5.0f, 5.0f);
		ImGui::End();

		ImGui::Begin("polygon2");
		ImGui::ColorEdit3("color", (float*)&imGuiPolygon[1].color);
		ImGui::SliderFloat3("scale", &imGuiPolygon[1].scale.x, -0.0f, 5.0f);
		ImGui::SliderFloat3("rotate", &imGuiPolygon[1].rotate.x, -5.0f, 5.0f);
		ImGui::SliderFloat3("translate", &imGuiPolygon[1].translate.x, -5.0f, 5.0f);
		ImGui::End();


		for (int i = 0; i < Count; i++) {
			imGuiPolygon[i].matrix = MakeAffineMatrix(imGuiPolygon[i].scale, imGuiPolygon[i].rotate, imGuiPolygon[i].translate);
			polygon_[i]->Draw(imGuiPolygon[i].matrix, imGuiPolygon[i].color);
		}*/

		/*	ImGui::Begin("Sprite");

			ImGui::SliderFloat3("scale", &imGuiSprite.scale.x, -0.0f, 5.0f);
			ImGui::SliderFloat3("rotate", &imGuiSprite.rotate.x, -5.0f, 5.0f);
			ImGui::SliderFloat3("translate", &imGuiSprite.translate.x, -500.0f, 500.0f);
			ImGui::End();
			imGuiSprite.matrix= MakeAffineMatrix(imGuiSprite.scale, imGuiSprite.rotate, imGuiSprite.translate);

			SpriteTex->Darw(imGuiSprite.matrix);

			ImGui::Begin("sphere");
			ImGui::ColorEdit3("color", (float*)&imGuiSphere[0].color);
			ImGui::SliderFloat3("scale", &imGuiSphere[0].scale.x, -0.0f, 5.0f);
			ImGui::SliderFloat3("rotate", &imGuiSphere[0].rotate.x, -5.0f, 5.0f);
			ImGui::SliderFloat3("translate", &imGuiSphere[0].translate.x, -5.0f, 5.0f);
			ImGui::End();


			imGuiSphere[0].rotate.y += 0.02f;

			imGuiSphere[0].matrix = MakeAffineMatrix(imGuiSphere[0].scale, imGuiSphere[0].rotate, imGuiSphere[0].translate);
			sphere_->Draw(imGuiSphere[0].matrix);*/
		


		if (Input::GetInstance()->PushKey(DIK_A)) {


			ImGui::Begin("3D");
			ImGui::ColorEdit3("color", (float*)&imGui3D[0].color);
			ImGui::SliderFloat3("scale", &imGui3D[0].scale.x, -0.0f, 5.0f);
			ImGui::SliderFloat3("rotate", &imGui3D[0].rotate.x, -10.0f, 10.0f);
			ImGui::SliderFloat3("translate", &imGui3D[0].translate.x, -5.0f, 5.0f);
			ImGui::End();
			imGui3D[0].matrix = MakeAffineMatrix(imGui3D[0].scale, imGui3D[0].rotate, imGui3D[0].translate);
			obj3D->Draw(imGui3D[0].matrix);
		}

		
		




		ImguiManager::EndFrame();
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

	obj3D->Release();
	delete obj3D;
	imageLoading->End();
	delete 	imageLoading;
	sphere_->Release();

	SpriteTex->Release();

	TextureCompileShader::Release();
	PolygonCompileShader::Release();
	SpriteCompileShader::Release();
	LightCompileShader::Release();

	TexturePSO::Release();
	PolygonPSO::Release();
	SpritePSO::Release();
	LightPSO::Release();



	ImguiManager::Release();
	DxCommon::Release();


	return 0;
}

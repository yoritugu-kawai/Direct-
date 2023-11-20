#pragma once
#include"../Math/Math.h"
#include"../Base/DxCommon.h"
#include"../Base/SpritePSO.h"
#include"../Base/ImageLoading.h"
class  Sprite
{
public:
	static Sprite* GetInstance();
	
	static void Initialize(TexProeerty  tex, Vector4 x, Vector4 y, Vector4 xy);
	static void Vertex();
	static void Darw(Matrix4x4 m);
	static void Release();

	static ID3D12Resource* CreateBufferResource(size_t sizeInbyte);
private:

	//
	D3D12_VERTEX_BUFFER_VIEW vertexBufferViewSprite{};
	D3D12_INDEX_BUFFER_VIEW indexBufferViewSprite{};

	VertexData* VertexDataSprite = nullptr;
	ID3D12Resource* vertexResourceSprite;
	ID3D12Resource* transformationMatrixResourceSprote;
	ID3D12Resource* materialResource;
	ID3D12Resource* indexResourceSprite;


	


	TexProeerty  tex_;
	Vector4 transX_ = { 0.0f,0.0f,0.0f };
	Vector4 transY_ = { 0.0f,0.0f,0.0f };
	Vector4 transXY_ = { 0.0f,0.0f,0.0f };

};



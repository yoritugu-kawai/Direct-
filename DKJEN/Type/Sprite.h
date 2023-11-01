#pragma once
#include"../Math/Math.h"
#include"../Base/DxCommon.h"
#include"../Base/SpritePSO.h"
#include"../Base/ImageLoading.h"
class  Sprite
{
public:
	void Initialize(TexProeerty  tex, Vector4 x, Vector4 y, Vector4 xy);
	void Vertex();
	void Darw(Matrix4x4 m);
	void Release();

	ID3D12Resource* CreateBufferResource(size_t sizeInbyte);
private:

	//
	D3D12_VERTEX_BUFFER_VIEW vertexBufferViewSprite{};
	D3D12_INDEX_BUFFER_VIEW indexBufferViewSprite{};

	VerteData* VertexDataSprite = nullptr;
	ID3D12Resource* vertexResourceSprite;
	ID3D12Resource* transformationMatrixResourceSprote;
	ID3D12Resource* materialResource;
	ID3D12Resource* indexResourceSprite;

	Matrix4x4* transformationMatrixDataSprite = nullptr;
	Transfrom transformSprite{ {1.0f,1.0f,1.0f},{0.0f,0.0f,0.0f},{0.0f,0.0f,0.0f} };


	TexProeerty  tex_;
	Vector4 transX_ = { 0.0f,0.0f,0.0f };
	Vector4 transY_ = { 0.0f,0.0f,0.0f };
	Vector4 transXY_ = { 0.0f,0.0f,0.0f };
};



#pragma once
#include"Polygon.h"
#include"../Base/SpritePSO.h"
class  Sprite
{
public:
	void Initialize();
	void Vertex();
	void Darw();
	void Release();

	 ID3D12Resource* CreateBufferResource(size_t sizeInbyte);
private:

	//
	D3D12_VERTEX_BUFFER_VIEW vertexBufferViewSprite{};
	VerteData* VertexDataSprite = nullptr;
	ID3D12Resource* vertexResourceSprite;
	ID3D12Resource* transformationMatrixResourceSprote;
	ID3D12Resource* materialResource;

	Matrix4x4* transformationMatrixDataSprite = nullptr;
	Transfom transformSprite{ {1.0f,1.0f,1.0f},{0.0f,0.0f,0.0f},{0.0f,0.0f,0.0f} };
	
	
	TexProeerty  tex_;
	RoadTexture* Roadtex_ = new RoadTexture;
};



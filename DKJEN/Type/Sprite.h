#pragma once
#include"Polygon.h"
class  Sprite
{
public:
	void Initialize();
	void Vertex();
	void Darw();
	void Release();
private:
	PolygonType* polygon_ = new  PolygonType;
	//
	D3D12_VERTEX_BUFFER_VIEW vertexBufferViewSprite{};
	VerteData* VertexDataSprite = nullptr;
	ID3D12Resource* vertexResourceSprite;
	ID3D12Resource* transformationMatrixResourceSprote;
	Matrix4x4* transformationMatrixDataSprite = nullptr;
	Transfom transformSprite{ {1.0f,1.0f,1.0f},{0.0f,0.0f,0.0f},{0.0f,0.0f,0.0f} };

};



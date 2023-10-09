#pragma once
#include"Polygon.h"
class  Sprite
{
public:
	void Initialize();
	void Vertex();
	void Darw();
private:
	PolygonType* polygon_ = new  PolygonType;
	//
	ID3D12Resource* vertexResourceSprite;
	ID3D12Resource* transformationMatrixResourceSprote;
};

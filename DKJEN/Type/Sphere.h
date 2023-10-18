#pragma once
#include"../Base/DxCommon.h"
#include"../Math/Math.h"
#include"../Base/PolygonPSO.h"
#include"../Base/RoadTexture.h"
#include"../Base/SpritePSO.h"

class Sphere
{
public:

	void Initialize(Vector4 pos, float size);

	void Draw(Matrix4x4 m);

	void Release();



	D3D12_VERTEX_BUFFER_VIEW VertexCreateBufferView(size_t sizeInbyte, ID3D12Resource* Resource, int size);

	ID3D12Resource* CreateBufferResource(size_t sizeInbyte);
private:

	void CommandCall();
	ID3D12Resource* Vertex;
	ID3D12Resource* materialResource;
	ID3D12Resource* wvpResource;

	
	D3D12_VERTEX_BUFFER_VIEW bufferView_;
	
	TexProeerty  tex_;
	
	RoadTexture* Roadtex_ = new RoadTexture;
	

	Transfom transform{ {1.0f,1.0f,1.0f},{0.0f,0.0f,0.0f},{0.0f,0.0f,0.0f} };

	Vector4 color_ = { 1,1,1,1 };
	Vector4 centerPos_ = { 0,0,0,0 };
	float radious_ = 1.0f;
	Matrix4x4 viewMatrix = MakeIdentity4x4();
	
	const int VertexNum_ = 16;
};




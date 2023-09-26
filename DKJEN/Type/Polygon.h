#pragma once
#include"../Math/Math.h"
#include"../Base/DxCommon.h"
#include"../Base/PipelineState.h"
#include"Texture.h"
class PolygonType
{
public:
	void Initialize(Vector4 lefe, Vector4 top, Vector4 right, Vector4 Color);
	void Draw(TexProeerty  tex, float speed);
	void Release();
	//
	static ID3D12Resource* CreateBufferResource(size_t sizeInbyte);
	static D3D12_VERTEX_BUFFER_VIEW VertexCreateBufferView(size_t sizeInbyte, ID3D12Resource* Resource, int size);

private:

	Vector4 lefe_ = { 0.0f,0.0f,0.0f };
	Vector4 top_ = { 0.0f,0.0f,0.0f };
	Vector4 right_ = { 0.0f,0.0f,0.0f };
	
	Vector4 Color_ = { 0.0f,0.0f,1.0f,1.0f };
	Transfom transfom{ {1.0f,1.0f,1.0f},{0.0f,0.0f,0.0f},{0.0f,0.0f,0.0f} };

	const float size = 0.1f;
	DxCommon dxCommmon_;
	//
	ID3D12Resource* Vertex;

	ID3D12Resource* materialResource;
	ID3D12Resource* wvpResource;
	//
	D3D12_VERTEX_BUFFER_VIEW bufferView_;
	//
	Transfom cameratransform = { {1.0f,1.0f,1.0f},{0.0f,0.0f,0.0f},{0.0f,0.0f,-5.0f} };
};

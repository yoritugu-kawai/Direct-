#pragma once
#include"../dase/WinApp.h"
#include"../dase/Dxcommen.h"
#include"../math/mathStrt.h"

class PolygoType
{
public:
	PolygoType();
	~PolygoType();

	void Initiluze(DxCommon* dxcommon, int32_t  kClientWidth, int32_t kClientHeight, Vector4 lefe, Vector4 top, Vector4 right);
	void Update(int32_t windowsizeWidth, int32_t windowsizeHeight);
	void Move();
	ID3D12Resource* CreateBufferResource(ID3D12Device* device, size_t sizeInBytes);
	void Draw(Vector4 color);
	Vector4 Color(unsigned int color);
private:

	//
	D3D12_VIEWPORT viewport{};
	D3D12_RECT scissorRect{};
	///
	DxCommon* dxcommon_ = nullptr;
	ID3D12Resource* vertexResource = nullptr;
	D3D12_VERTEX_BUFFER_VIEW vertexBufferView{};
	//
	ID3D12Resource* materialResource;
	ID3D12Resource* wvpResource;
	Transfom transfom{ {1.0f,1.0f,1.0f},{0.0f,0.0f,0.0f},{0.0f,0.0f,0.0f} };
	//
	int32_t kClientWidth_;
	int32_t kClientHeight_;
	Vector4 lefe_;
	Vector4 top_;
	Vector4 right_;
	Vector4 color_;

};


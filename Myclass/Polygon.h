#pragma once
#include"WinApp.h"
#include"Dxcommen.h"
#include"../PolygonStrt.h"

class PolygoType
{
public:
	PolygoType();
	~PolygoType();

	void Initiluze(DxCommon* dxcommon, int32_t  kClientWidth, int32_t kClientHeight);
	void Update();
	void CreateBufferResource();
	void Draw(Vector4 lefe, Vector4 top, Vector4 right);
private:

	//
	D3D12_VIEWPORT viewport{};
	D3D12_RECT scissorRect{};
	///
	DxCommon* dxcommon_ = nullptr;
	ID3D12Resource* vertexResource;
	D3D12_VERTEX_BUFFER_VIEW vertexBufferView{};
	//
	int32_t kClientWidth_;
	int32_t kClientHeight_;
};


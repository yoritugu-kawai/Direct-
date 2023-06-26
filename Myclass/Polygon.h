#pragma once
#include"WinApp.h"
#include"Dxcommen.h"
#include"../PolygonStrt.h"

class PolygoType
{
public:
	PolygoType();
	~PolygoType();
	void Initiluze(DxCommon* dxcommon);
	void Update(int32_t windowsizeWidth, int32_t windowsizeHeight);

	BufferResource CreateBufferResource();
	void Triangle(Vector4 lefe, Vector4 top, Vector4 right, ID3D12Resource* vertexResource);
	void Call(BufferResource bufferResource);
	//void Release( IDxcBlob* pixelShaderBlob, IDxcBlob* vertexShaderBlob, ID3DBlob* signatureBlob, ID3DBlob* errorBlob, ID3D12Resource* vertexResource);
	void Draw(Vector4 lefe, Vector4 top, Vector4 right, ID3D12Resource* vertexResource, BufferResource bufferResource);
private:


	//////ⅤertexResource作成

	//
	D3D12_VIEWPORT viewport{};
	D3D12_RECT scissorRect{};
	///
	DxCommon* dxcommon_ = nullptr;
};


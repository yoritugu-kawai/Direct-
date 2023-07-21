#pragma once
#include"../dase/WinApp.h"
#include"../dase/Dxcommen.h"
#include"../math/mathStrt.h"

class PolygoType
{
public:
	PolygoType();
	~PolygoType();

	void Initiluze(DxCommon* dxcommon);
	void Update(int32_t windowsizeWidth, int32_t windowsizeHeight);
	void Move();
	ID3D12Resource* CreateBufferResource(ID3D12Device* device, size_t sizeInBytes);
	
	void Triangle(Vector4 lefe, Vector4 top, Vector4 right, unsigned int color);
	void Call();
	//void Release( IDxcBlob* pixelShaderBlob, IDxcBlob* vertexShaderBlob, ID3DBlob* signatureBlob, ID3DBlob* errorBlob, ID3D12Resource* vertexResource);
	void Draw(Vector4 lefe, Vector4 top, Vector4 right, unsigned int color);
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

};


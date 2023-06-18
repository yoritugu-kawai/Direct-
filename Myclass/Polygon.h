#pragma once
#include"WinApp.h"
#include"Dxcommen.h"
#include"../PolygonStrt.h"

class PolygonApp
{
public:
	PolygonApp();
	~PolygonApp();
	void Initialize(int32_t windowsizeWidth, int32_t windowsizeHeight, ID3D12GraphicsCommandList* commandList);
	
	BufferResource CreateBufferResource(ID3D12Device* device);
	void Triangle(Vector4 lefe, Vector4 top, Vector4 right,ID3D12Resource* vertexResource);
	void Call(ID3D12GraphicsCommandList* commandList, ID3D12RootSignature* rootSignature, ID3D12PipelineState* graphicsPipelineState, BufferResource bufferResource);
	void Release(ID3D12RootSignature* rootSignature, ID3D12PipelineState* graphicsPipelineState, IDxcBlob* pixelShaderBlob, IDxcBlob* vertexShaderBlob, ID3DBlob* signatureBlob, ID3DBlob* errorBlob, ID3D12Resource* vertexResource);
	void Draw(Vector4 lefe, Vector4 top, Vector4 right, ID3D12GraphicsCommandList* commandList, ID3D12RootSignature* rootSignature, ID3D12PipelineState* graphicsPipelineState, ID3D12Resource* vertexResource, BufferResource bufferResource);
private:

	
	//////ⅤertexResource作成

	//
	D3D12_VIEWPORT viewport{};
	D3D12_RECT scissorRect{};
	//VerteBufferView作成
	
};


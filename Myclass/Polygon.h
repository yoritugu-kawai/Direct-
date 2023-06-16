#pragma once
#include<Windows.h>
#include <cstdint>
#include<string>
#include<format>
#include<d3d12.h>
#include<dxgi1_6.h>
#include<cassert>
#include<dxgidebug.h>
#include"WinApp.h"
#include"Dxcommen.h"
#include<dxcapi.h>

#pragma comment(lib,"dxguid.lib")
#pragma comment(lib,"d3d12.lib")
#pragma comment(lib,"dxgi.lib")
#pragma comment(lib,"dxcompiler.lib")

class PolygonApp
{
public:
	PolygonApp();
	~PolygonApp();
	void Initialize(int32_t windowsizeWidth, int32_t windowsizeHeight,ID3D12Device*device, HRESULT hr);
	void Triangle(Vector4 lefe, Vector4 top, Vector4 right, ID3D12GraphicsCommandList* commandList, ID3D12RootSignature* rootSignature, ID3D12PipelineState* graphicsPipelineState);
	void DrawCall(ID3D12GraphicsCommandList* commandList, ID3D12RootSignature* rootSignature, ID3D12PipelineState* graphicsPipelineState);
	void Release(ID3D12RootSignature* rootSignature, ID3D12PipelineState* graphicsPipelineState, IDxcBlob* pixelShaderBlob, IDxcBlob* vertexShaderBlob, ID3DBlob* signatureBlob, ID3DBlob* errorBlob);
private:
	
	//////ⅤertexResource作成
	ID3D12Resource* vertexResource;
	//
	D3D12_VIEWPORT viewport{};
	D3D12_RECT scissorRect{};
	//VerteBufferView作成
	D3D12_VERTEX_BUFFER_VIEW vertexBufferView{};
};


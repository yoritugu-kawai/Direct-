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
#include"DixApp.h"
#include<dxcapi.h>

#pragma comment(lib,"dxguid.lib")
#pragma comment(lib,"d3d12.lib")
#pragma comment(lib,"dxgi.lib")
#pragma comment(lib,"dxcompiler.lib")
struct Vector4
{
	float x;
	float y;
	float z;
	float w;
};
class DixApp
{
public:
	
	void Initialize(int32_t windowsizeWidth, int32_t windowsizeHeight, HWND hwnd);
	void POS();
	void Release(HWND hwnd);

	
	static void CreateFactory(IDXGIFactory7* dxgiFactory, IDXGIAdapter4* useAdapter);



private:
	IDXGIFactory7* dxgiFactory = nullptr;
	HRESULT hr;
	IDXGIAdapter4* useAdapter = nullptr;
	ID3D12Resource* vertexResource = nullptr;
	ID3D12InfoQueue* infoQueue = nullptr;
	ID3D12CommandQueue* commandQueue = nullptr;
	ID3D12CommandAllocator* commandAllocator = nullptr;
	ID3DBlob* signatureBlob = nullptr;
	ID3DBlob* errorBlob = nullptr;
	ID3D12DescriptorHeap* rtvDescriptorHeap = nullptr;
	ID3D12Resource* swapChainResources[2] = { nullptr };
	ID3D12Fence* fence = nullptr;
	IDXGISwapChain4* swapChain = nullptr;
	HANDLE fenceEvent;
	IDxcIncludeHandler* includeHandler = nullptr;
	IDxcUtils* dxcUtils = nullptr;
	IDxcCompiler3* dxcCompiler = nullptr;
	IDxcBlob* pixelShaderBlob;
	IDxcBlob* vertexShaderBlob;
	ID3D12Device* device = nullptr;
	ID3D12GraphicsCommandList* commandList = nullptr;
	ID3D12PipelineState* graphicsPipelineState = nullptr;
	ID3D12RootSignature* rootSignature = nullptr;
};

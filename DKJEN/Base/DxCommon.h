#pragma once
#include"WinApp.h"
#include"../Math/Math.h"

class DxCommon
{
public:

	void Initialize(int32_t windowsizeWidth, int32_t windowsizeHeight, HWND hwnd);

	void Release(HWND hwnd);

private:
	IDXGIFactory7* dxgiFactory = nullptr;
	HRESULT hr;
	IDXGIAdapter4* useAdapter = nullptr;
	ID3D12Device* device = nullptr;
	ID3D12InfoQueue* infoQueue = nullptr;
	ID3D12CommandQueue* commandQueue = nullptr;
	ID3D12CommandAllocator* commandAllocator = nullptr;
	ID3D12GraphicsCommandList* commandList = nullptr;
	ID3D12DescriptorHeap* rtvDescriptorHeap = nullptr;
	ID3D12Resource* swapChainResources[2] = { nullptr };
	ID3D12Fence* fence = nullptr;
	IDXGISwapChain4* swapChain = nullptr;
	HANDLE fenceEvent;
};

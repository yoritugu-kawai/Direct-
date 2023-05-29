#pragma once
#include<Windows.h>
#include <cstdint>
#include<string>
#include<format>
#include<d3d12.h>
#include<dxgi1_6.h>
#include<cassert>
#include<dxgidebug.h>
#include<dxcapi.h>
#include"WinApp.h"


#pragma comment(lib,"dxguid.lib")
#pragma comment(lib,"d3d12.lib")
#pragma comment(lib,"dxgi.lib")
#pragma comment(lib,"dxcompiler.lib")

class DixApp
{
public:
	std::wstring ConvertString(const std::string& str);
	std::string ConvertString(const std::wstring& str);
	void Log(const std::string& message);
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

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
	void Initialize(const int32_t kClientWidth, const int32_t kClientHeight);
	void Debug();
	void Ma();
	void Release();
private:
	HRESULT hr;
	HANDLE fenceEvent;
	uint64_t fenceValue;
	ID3D12Fence* fence = nullptr;
	ID3D12Resource* swapChainResources[2] = { nullptr };;
	ID3D12GraphicsCommandList* commandList = nullptr;
	ID3D12CommandQueue* commandQueue = nullptr;
	ID3D12CommandAllocator* commandAllocator = nullptr;
	IDXGISwapChain4* swapChain = nullptr;
	ID3D12DescriptorHeap* rtvDescriptorHeap = nullptr;
	ID3D12Device* device = nullptr;
	IDXGIAdapter4* useAdapter = nullptr;
	IDXGIFactory7* dxgiFactory = nullptr;
	ID3D12Debug1* deugController = nullptr;
};

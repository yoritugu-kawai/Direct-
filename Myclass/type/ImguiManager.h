#pragma once
#include"../dase/WinApp.h"
#include"../dase/Dxcommen.h"
class ImguiManager
{
public:
	void Initialize(HWND hwnd, ID3D12Device* device, DXGI_SWAP_CHAIN_DESC1 swapChainDesc, 
		D3D12_RENDER_TARGET_VIEW_DESC rtvDesc, ID3D12DescriptorHeap* srvDescriptorHeap);
	void BeginFrame(ID3D12DescriptorHeap* srvDescriptorHeap, ID3D12GraphicsCommandList* commandList);
	void EndFrame(ID3D12GraphicsCommandList* commandList);
	void Release();
private:
	WinApp* winApp_=nullptr;
	DxCommon* dxCommon_ = nullptr;
};

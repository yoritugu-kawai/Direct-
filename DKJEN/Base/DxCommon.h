#pragma once
#include"WinApp.h"
#include"../Math/Math.h"

class DxCommon
{
public:
	/// <summary>
	/// コマンド系
	/// </summary>
	void CreateCommandQueue();
	void CreateCommandList();
	/// <summary>
	/// スワップチェーン
	/// </summary>
	void CreateSwapChain(int32_t kClientWidth, int32_t kClientHeight, HWND hwnd);
	void CreateSwapResce();
	/// <summary>
	/// ヒープ
	/// </summary>
	void CreateDescriptorHeap();
	/// <summary>
	/// RTV
	/// </summary>
	void CreateRTV();

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="kClientWidth"></param>
	/// <param name="kClientHeight"></param>
	/// <param name="hwnd"></param>
	void Initialize(int32_t kClientWidth, int32_t kClientHeight, HWND hwnd);

	void k(int32_t kClientWidth, int32_t kClientHeight, HWND hwnd);
	//解放
	void Release(HWND hwnd);

private:
	//WinApp* winApp_ = nullptr;


	/////
	/// <summary>
	/// ファクトリーの作成
	/// </summary>
	IDXGIFactory7* dxgiFactory;//
	HRESULT hr;//
	/// <summary>
	/// アダプターの作成
	/// </summary>
	IDXGIAdapter4* useAdapter;//
	/// <summary>
	/// Deviceの作成
	/// </summary>
	ID3D12Device* device;//
	/// <summary>
	/// エラー警告
	/// </summary>
	ID3D12InfoQueue* infoQueue = nullptr;//


	/// <summary>
	/// コマンド
	/// </summary>
	ID3D12CommandQueue* commandQueue;//
	ID3D12GraphicsCommandList* commandList;//
	D3D12_RESOURCE_BARRIER barrier{};//
	/// <summary>
	/// スワップチェーン
	/// </summary>
	IDXGISwapChain4* swapChain;//
	/// <summary>
	/// ヒープ
	/// </summary>
	ID3D12DescriptorHeap* rtvDescriptorHeap;//
	/// <summary>
	/// スワップチェーンのリリースを出す
	/// </summary>
	ID3D12Resource* swapChainResources[2];//
	/// <summary>
	/// 
	/// </summary>
	D3D12_CPU_DESCRIPTOR_HANDLE rtvHandles[2];//
	/// <summary>
	/// コマンド
	/// </summary>
	ID3D12CommandAllocator* commandAllocator;//
	/// <summary>
	/// デバック
	/// </summary>

	//フェンスイベント
	ID3D12Fence* fence;//
	uint64_t fenceValue = 0;//
	HANDLE fenceEvent;//
	//POS
	ID3D12PipelineState* graphicsPipelineState;/*後々の可能性あり*/
	/*---------ルートシグネチャの設定---------*/
	ID3DBlob* signatureBlob;//
	ID3DBlob* errorBlob;//
	ID3D12RootSignature* rootSignature;//
	/*-----シェイダ－コンパイル-------*/
	IDxcBlob* vertexShaderBlob;/*後々の可能性あり*/
	IDxcBlob* pixelShaderBlob;/*後々の可能性あり*/
	/*DIX*/
	IDxcUtils* dxcUtils;/*後々の可能性あり*/
	IDxcCompiler3* dxcCompiler;/*後々の可能性あり*/
	IDxcIncludeHandler* includeHandler;/*後々の可能性あり*/
};

#pragma once
#include"../math/mathStrt.h"

class DxCommon
{
public:
	void DIX();
	/// <summary>
	/// デバック
	/// </summary>
	void DebugController();
	void DebugInfoQueue();
	/// <summary>
	/// DIXの初期設定
	/// </summary>
	void CreateFactory();
	void CreateAdapter();
	void CreateDevice();
	/// <summary>
	/// 青画面
	/// </summary>
	void CreateCommandQueue();
	void CreateCommandList();
	void CreateSwapChain(int32_t kClientWidth, int32_t kClientHeight, HWND hwnd);
	void CreateDescriptorHeap();
	void CreateSwapResce();
	void CreateRTV();
	//ループさせる
	void CommandLoad();
	void Commandkick();
	//
	void CreateFeneEvent();
	/// <summary>
	///  DIXの初期化
	/// </summary>
	/// <param name="kClientWidth"></param>
	/// <param name="kClientHeight"></param>
	/// <param name="hwnd"></param>
	/// <returns></returns>
	void Initialize(int32_t kClientWidth, int32_t kClientHeight, HWND hwnd);
	void BeginFrame();
	void POS();
	void Release(HWND hwnd);
	void EndFrame();
	///ポリゴンイニシャライズ
	ID3D12Device* deviceGet() { return device; }
	HRESULT hrGet() { return hr; }
	///ポリゴンコール
	ID3D12GraphicsCommandList* commandListGet(){ return commandList; }
	ID3D12RootSignature* rootSignatureGet(){return  rootSignature;}
	ID3D12PipelineState* graphicsPipelineStateGet(){return  graphicsPipelineState;}
	//ポリゴンリリース
	IDxcBlob* pixelShaderBlobGet() {return pixelShaderBlob;}
	IDxcBlob* vertexShaderBlobGet() {return vertexShaderBlob;}
	ID3DBlob* signatureBlobGet() { return signatureBlob; }
	ID3DBlob* errorBlobGet() { return errorBlob; }
private:
	/// <summary>
	/// ファクトリーの作成
	/// </summary>
	IDXGIFactory7* dxgiFactory;
	HRESULT hr;//
	/// <summary>
	/// アダプターの作成
	/// </summary>
	IDXGIAdapter4* useAdapter;
	/// <summary>
	/// Deviceの作成
	/// </summary>
	ID3D12Device* device;//
	/// <summary>
	/// コマンド
	/// </summary>
	ID3D12CommandQueue* commandQueue;
	ID3D12GraphicsCommandList* commandList;//
	D3D12_RESOURCE_BARRIER barrier{};
	/// <summary>
	/// スワップチェーン
	/// </summary>
	IDXGISwapChain4* swapChain;
	/// <summary>
	/// ヒープ
	/// </summary>
	ID3D12DescriptorHeap* rtvDescriptorHeap;
	/// <summary>
	/// スワップチェーンのリリースを出す
	/// </summary>
	ID3D12Resource* swapChainResources[2];
	/// <summary>
	/// 
	/// </summary>
	D3D12_CPU_DESCRIPTOR_HANDLE rtvHandles[2];
	/// <summary>
	/// コマンド
	/// </summary>
	ID3D12CommandAllocator* commandAllocator;
	/// <summary>
	/// デバック
	/// </summary>

	//フェンスイベント
	ID3D12Fence* fence;
	uint64_t fenceValue;
	HANDLE fenceEvent;
	//POS
	ID3D12PipelineState* graphicsPipelineState;//
		/*---------ルートシグネチャの設定---------*/
	ID3DBlob* signatureBlob;//
	ID3DBlob* errorBlob;//
	ID3D12RootSignature* rootSignature;//
	/*-----シェイダ－コンパイル-------*/
	IDxcBlob* vertexShaderBlob;//
	IDxcBlob* pixelShaderBlob;//
	/*DIX*/
	IDxcUtils* dxcUtils;
	IDxcCompiler3* dxcCompiler;
	IDxcIncludeHandler* includeHandler;
};

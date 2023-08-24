#pragma once
#include"WinApp.h"
#include"../Math/Math.h"

class DxCommon
{
public:
	static DxCommon* GetInstance();

	static IDxcBlob* CompileShader(
		// CompilerするShaderファイルへのパス
		const std::wstring& filePath,
		// Compilerに使用するProfile
		const wchar_t* profile,
		// 初期化で生成したものを3つ
		IDxcUtils* dxcUtils,
		IDxcCompiler3* dxcCompiler,
		IDxcIncludeHandler* includeHandler);

	/// <summary>
	/// コマンド系
	/// </summary>
	static void CreateCommands();

	static void CommandLoad();
	static void Commandkick();
	//ループ
	static void BeginFrame();
	static void EndFrame();

	/// <summary>
	/// スワップチェーン
	/// </summary>
	static void CreateSwapChain();
	static void CreateSwapResce();
	/// <summary>
	/// ヒープ
	/// </summary>
	static void CreateDescriptorHeap();
	/// <summary>
	/// RTV
	/// </summary>
	static void CreateRTV();
	/// <summary>
	/// エラー
	/// </summary>
	static void DebugInfoQueue();
	static void CreateDxgiFactory();

	//
	static void CreateFeneEvent();
	static void CreateDevice();
	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="kClientWidth"></param>
	/// <param name="kClientHeight"></param>
	/// <param name="hwnd"></param>
	static void Initialize();

	
	//解放
	static void Release();

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
	

	ID3D12Debug1* debugController = nullptr;
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
	ID3D12Fence* fence=nullptr;//
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
	
};

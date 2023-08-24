#include"DxCommon.h"

DxCommon* DxCommon::GetInstance()
{
	static DxCommon instance;

	return &instance;
}

IDxcBlob* DxCommon::CompileShader(
	// CompilerするShaderファイルへのパス
	const std::wstring& filePath,
	// Compilerに使用するProfile
	const wchar_t* profile,
	// 初期化で生成したものを3つ
	IDxcUtils* dxcUtils,
	IDxcCompiler3* dxcCompiler,
	IDxcIncludeHandler* includeHandler)
{
	/* --- 1. hlslファイルを読む --- */

	// これからシェーダーをコンパイルする旨をログに出す
	Log(ConvertString(std::format(L"Begin CompileShader, path:{}, profile:{}\n", filePath, profile)));
	// hlslを読み込む
	IDxcBlobEncoding* shaderSource = nullptr;
	HRESULT hr = dxcUtils->LoadFile(filePath.c_str(), nullptr, &shaderSource);
	// 読み込めなかったら止める
	assert(SUCCEEDED(hr));
	// 読み込んだファイルの内容を設定する
	DxcBuffer shaderSourceBuffer;
	shaderSourceBuffer.Ptr = shaderSource->GetBufferPointer();
	shaderSourceBuffer.Size = shaderSource->GetBufferSize();
	shaderSourceBuffer.Encoding = DXC_CP_UTF8; // UTF8の文字コードであることを通知


	/* --- 2.Compilerする --- */

	LPCWSTR arguments[] = {
		filePath.c_str(),  // コンパイル対象のhlslファイル名
		L"-E", L"main",  // エントリーポイントの指定。基本的にmain以外にはしない
		L"-T", profile,  // ShaderProfileの設定
		L"-Zi", L"-Qembed_debug",  // デバッグ用の情報を埋め込む
		L"-Od",  // 最適化を外しておく
		L"-Zpr",  // メモリレイアウトは行優先
	};
	// 実際にShaderをコンパイルする
	IDxcResult* shaderResult = nullptr;
	hr = dxcCompiler->Compile(
		&shaderSourceBuffer,        // 読み込んだファイル
		arguments,					// コンパイルオプション
		_countof(arguments),		// コンパイルオプションの数
		includeHandler,				// includeが含まれた諸々
		IID_PPV_ARGS(&shaderResult)	// コンパイル結果
	);
	// コンパイルエラーではなくdxcが起動できないなど致命的な状況
	assert(SUCCEEDED(hr));


	/* --- 3. 警告・エラーが出てないか確認する --- */
	IDxcBlobUtf8* shaderError = nullptr;
	shaderResult->GetOutput(DXC_OUT_ERRORS, IID_PPV_ARGS(&shaderError), nullptr);
	if (shaderError != nullptr && shaderError->GetStringLength() != 0) {
		// 警告・エラーゼッタイ
		Log(shaderError->GetStringPointer());
		assert(false);
	}


	/* --- 4. Compiler結果を受け取って返す --- */

	// コンパイル結果から実行用のバイナリ部分を取得
	IDxcBlob* shaderBlob = nullptr;
	hr = shaderResult->GetOutput(DXC_OUT_OBJECT, IID_PPV_ARGS(&shaderBlob), nullptr);
	assert(SUCCEEDED(hr));
	// 成功したログを出す
	Log(ConvertString(std::format(L"Compile Succeded, path{}, profile:{}\n", filePath, profile)));
	// もう使わないリソースを解放
	shaderSource->Release();
	shaderResult->Release();
	// 実行用のバイナリを返却
	return shaderBlob;
}



/************************************************/
/****************   コマンド組   ****************/
/************************************************/
void DxCommon::CreateCommands()
{
	// コマンドキュー作成

	D3D12_COMMAND_QUEUE_DESC commandQueueDesc{};
	ID3D12Device* device=DxCommon::GetInstance()->device;//
	HRESULT hr;//
	ID3D12CommandQueue* commandQueue;//
	ID3D12GraphicsCommandList* commandList;//
	ID3D12CommandAllocator* commandAllocator;//
	//
	hr = device->CreateCommandQueue(&commandQueueDesc,
		IID_PPV_ARGS(&commandQueue));
	// コマンドキュー作成がうまくいかなかった
	assert(SUCCEEDED(hr));
	// CommandList作成

	hr = device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&commandAllocator));
	assert(SUCCEEDED(hr));

	hr = device->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, commandAllocator, nullptr,
		IID_PPV_ARGS(&commandList));
	assert(SUCCEEDED(hr));
	DxCommon::GetInstance()->device = device;
	DxCommon::GetInstance()->commandQueue = commandQueue;
	DxCommon::GetInstance()->commandList = commandList;
	DxCommon::GetInstance()->commandAllocator = commandAllocator;
}


void DxCommon::CommandLoad()
{
	IDXGISwapChain4* swapChain = DxCommon::GetInstance()->swapChain;
	D3D12_RESOURCE_BARRIER barrier{};//
	ID3D12Resource* swapChainResources[2];//
	swapChainResources[0] = DxCommon::GetInstance()->swapChainResources[0];
	swapChainResources[1] = DxCommon::GetInstance()->swapChainResources[1];
	ID3D12DescriptorHeap* rtvDescriptorHeap= DxCommon::GetInstance()->rtvDescriptorHeap;//
	D3D12_CPU_DESCRIPTOR_HANDLE rtvHandles[2];//
	rtvHandles[0] = DxCommon::GetInstance()->rtvHandles[0];
	rtvHandles[1] = DxCommon::GetInstance()->rtvHandles[1];
	ID3D12GraphicsCommandList* commandList = DxCommon::GetInstance()->commandList;//
	///
	UINT backBufferIndex = swapChain->GetCurrentBackBufferIndex();

	barrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
	barrier.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
	barrier.Transition.pResource = swapChainResources[backBufferIndex];
	barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_PRESENT;
	barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_RENDER_TARGET;
	commandList->ResourceBarrier(1, &barrier);

	commandList->OMSetRenderTargets(1, &rtvHandles[backBufferIndex], false, nullptr);
	float clearColor[] = { 0.1f,0.25f,0.5f,1.0f };
	commandList->ClearRenderTargetView(rtvHandles[backBufferIndex], clearColor, 0, nullptr);
	//
	DxCommon::GetInstance()->swapChain = swapChain;
	DxCommon::GetInstance()->barrier = barrier;
	DxCommon::GetInstance()->swapChainResources[0] = swapChainResources[0];
	DxCommon::GetInstance()->swapChainResources[1] = swapChainResources[1];
	DxCommon::GetInstance()->rtvDescriptorHeap = rtvDescriptorHeap;
	DxCommon::GetInstance()->rtvHandles[0] = rtvHandles[0];
	DxCommon::GetInstance()->rtvHandles[1] = rtvHandles[1];
	DxCommon::GetInstance()->commandList = commandList;
}

void DxCommon::Commandkick()
{
	IDXGISwapChain4* swapChain = DxCommon::GetInstance()->swapChain;
	D3D12_RESOURCE_BARRIER barrier = DxCommon::GetInstance()->barrier;
	ID3D12GraphicsCommandList* commandList = DxCommon::GetInstance()->commandList;//
	ID3D12CommandQueue* commandQueue = DxCommon::GetInstance()->commandQueue;//
	ID3D12CommandAllocator* commandAllocator = DxCommon::GetInstance()->commandAllocator;//
	ID3D12Fence* fence = DxCommon::GetInstance()->fence;//
	uint64_t fenceValue = DxCommon::GetInstance()->fenceValue;//
	HANDLE fenceEvent = DxCommon::GetInstance()->fenceEvent;//
	HRESULT hr;//
	////
	barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_RENDER_TARGET;
	barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_PRESENT;
	commandList->ResourceBarrier(1, &barrier);
	//
	hr = commandList->Close();
	assert(SUCCEEDED(hr));
	//コマンドキック
	ID3D12CommandList* commandLists[] = { commandList };
	commandQueue->ExecuteCommandLists(1, commandLists);
	swapChain->Present(0, 1);
	//シグナル
	fenceValue++;
	commandQueue->Signal(fence, fenceValue);
	if (fence->GetCompletedValue() < fenceValue) {
		fence->SetEventOnCompletion(fenceValue, fenceEvent);
		WaitForSingleObject(fenceEvent, INFINITE);
	}
	swapChain->Present(1, 0);

	///
	hr = commandAllocator->Reset();
	assert(SUCCEEDED(hr));
	hr = commandList->Reset(commandAllocator, nullptr);
	assert(SUCCEEDED(hr));

	DxCommon::GetInstance()->swapChain = swapChain;
	DxCommon::GetInstance()->barrier = barrier;
	DxCommon::GetInstance()->commandList = commandList;//
	DxCommon::GetInstance()->commandQueue = commandQueue;//
	DxCommon::GetInstance()->commandAllocator = commandAllocator;//
	DxCommon::GetInstance()->fence = fence;//
	DxCommon::GetInstance()->fenceValue = fenceValue;//
	DxCommon::GetInstance()->fenceEvent = fenceEvent;//

}

void DxCommon::BeginFrame()
{
	CommandLoad();
}
void DxCommon::EndFrame()
{
	Commandkick();

}

/************************************************/
/*************   スワップチェーン　**************/
/************************************************/
void DxCommon::CreateSwapChain()
{
	IDXGISwapChain4* swapChain = DxCommon::GetInstance()->swapChain;
	ID3D12CommandQueue* commandQueue = DxCommon::GetInstance()->commandQueue;//
	IDXGIFactory7* dxgiFactory = DxCommon::GetInstance()->dxgiFactory;//
	///
	//   スワップチェーン作成

	DXGI_SWAP_CHAIN_DESC1 swapChainDesc{};
	swapChainDesc.Width = WinApp::GetInstance()->Width();
	swapChainDesc.Height = WinApp::GetInstance()->Height();
	swapChainDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.BufferCount = 2;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
	HRESULT hr = dxgiFactory->CreateSwapChainForHwnd(
		commandQueue, WinApp::GetInstance()->GetHwnd(), 
		&swapChainDesc, nullptr, nullptr, reinterpret_cast<IDXGISwapChain1**>(&swapChain));
	assert(SUCCEEDED(hr));
	DxCommon::GetInstance()->commandQueue = commandQueue;//
	DxCommon::GetInstance()->dxgiFactory = dxgiFactory;//
	DxCommon::GetInstance()->swapChain = swapChain;

}
void DxCommon::CreateSwapResce()
{
	IDXGISwapChain4* swapChain = DxCommon::GetInstance()->swapChain;
	ID3D12Resource* swapChainResources[2];//
	swapChainResources[0] = DxCommon::GetInstance()->swapChainResources[0];
	swapChainResources[1] = DxCommon::GetInstance()->swapChainResources[1];
	///
	//スワップチェーンリソースを引っ張る

	HRESULT hr = swapChain->GetBuffer(0, IID_PPV_ARGS(&swapChainResources[0]));
	assert(SUCCEEDED(hr));
	hr = swapChain->GetBuffer(1, IID_PPV_ARGS(&swapChainResources[1]));
	assert(SUCCEEDED(hr));
	DxCommon::GetInstance()->swapChain = swapChain;
	DxCommon::GetInstance()->swapChainResources[0] = swapChainResources[0];
	DxCommon::GetInstance()->swapChainResources[1] = swapChainResources[1];
}

/************************************************/
/********************   ヒープ　*****************/
/************************************************/
void DxCommon::CreateDescriptorHeap()
{
	ID3D12DescriptorHeap* rtvDescriptorHeap; 
	ID3D12Device* device = DxCommon::GetInstance()->device;
	///
	//ディスクトップヒープ作成

	D3D12_DESCRIPTOR_HEAP_DESC rtvDescriptorHeapDesc{};
	rtvDescriptorHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
	rtvDescriptorHeapDesc.NumDescriptors = 2;
	HRESULT hr = device->CreateDescriptorHeap(&rtvDescriptorHeapDesc, IID_PPV_ARGS(&rtvDescriptorHeap));
	assert(SUCCEEDED(hr));
	CreateSwapResce();
	
	DxCommon::GetInstance()->device=device;
	DxCommon::GetInstance()->rtvDescriptorHeap = rtvDescriptorHeap;
	CreateRTV();

}

/************************************************/
/********************   RTV　 *******************/
/************************************************/

void DxCommon::CreateRTV()
{
	ID3D12DescriptorHeap* rtvDescriptorHeap= DxCommon::GetInstance()->rtvDescriptorHeap;
	ID3D12Resource* swapChainResources[2];//
	swapChainResources[0] = DxCommon::GetInstance()->swapChainResources[0];
	swapChainResources[1] = DxCommon::GetInstance()->swapChainResources[1];
	ID3D12Device* device = DxCommon::GetInstance()->device;
	D3D12_CPU_DESCRIPTOR_HANDLE rtvHandles[2];//
	rtvHandles[0] = DxCommon::GetInstance()->rtvHandles[0];
	rtvHandles[1] = DxCommon::GetInstance()->rtvHandles[1];
	////
	// RTVです
	D3D12_RENDER_TARGET_VIEW_DESC rtvDesc{};
	rtvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
	rtvDesc.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2D;

	D3D12_CPU_DESCRIPTOR_HANDLE rtvStarHandle = rtvDescriptorHeap->GetCPUDescriptorHandleForHeapStart();
	rtvHandles[0] = rtvStarHandle;
	device->CreateRenderTargetView(swapChainResources[0], &rtvDesc, rtvHandles[0]);

	rtvHandles[1].ptr = rtvHandles[0].ptr + device->GetDescriptorHandleIncrementSize(
		D3D12_DESCRIPTOR_HEAP_TYPE_RTV);

	device->CreateRenderTargetView(swapChainResources[1], &rtvDesc, rtvHandles[1]);
	//
	DxCommon::GetInstance()->device = device;
	DxCommon::GetInstance()->rtvDescriptorHeap = rtvDescriptorHeap;
	DxCommon::GetInstance()->swapChainResources[0] = swapChainResources[0];
	DxCommon::GetInstance()->swapChainResources[1] = swapChainResources[1];
	DxCommon::GetInstance()->rtvHandles[0] = rtvHandles[0];
	DxCommon::GetInstance()->rtvHandles[1] = rtvHandles[1];

}
/************************************************/
/****************   　エラー　   ****************/
/************************************************/

void DxCommon::DebugInfoQueue() {

#ifdef _DEBUG
	ID3D12InfoQueue* infoQueue = nullptr;//
	ID3D12Device* device = DxCommon::GetInstance()->device;
	///
	if (SUCCEEDED(device->QueryInterface(IID_PPV_ARGS(&infoQueue)))) {
		infoQueue->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_CORRUPTION, true);
		infoQueue->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_ERROR, true);
		infoQueue->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_WARNING, true);

		D3D12_MESSAGE_ID denyIds[]{
			D3D12_MESSAGE_ID_RESOURCE_BARRIER_MISMATCHING_COMMAND_LIST_TYPE
		};
		D3D12_MESSAGE_SEVERITY severities[] = { D3D12_MESSAGE_SEVERITY_INFO };
		D3D12_INFO_QUEUE_FILTER filter{};
		filter.DenyList.NumIDs = _countof(denyIds);
		filter.DenyList.pIDList = denyIds;
		filter.DenyList.NumSeverities = _countof(severities);
		filter.DenyList.pSeverityList = severities;

		infoQueue->PushStorageFilter(&filter);
		infoQueue->Release();

	}
	DxCommon::GetInstance()->device = device;
#endif // _DEBUG

}
void DxCommon::CreateDxgiFactory()
{
	IDXGIFactory7* dxgiFactory;//
	//GXGFactoryの生成

	//HRESULTはWindows系のエラーコードあり
	//関数が成功したかどうかをSUCCEDEDマクロで判定できる
	HRESULT hr = CreateDXGIFactory(IID_PPV_ARGS(&dxgiFactory));

	//初期化の根本的な部分でエラーが出た場合はプログラムが間違っているか、どうにもできない場合が多いのでassertにしておく
	assert(SUCCEEDED(hr));

	//アダプタ決定
	IDXGIAdapter4* useAdapter;
	// 良い順にアダプタ
	for (UINT i = 0; dxgiFactory->EnumAdapterByGpuPreference(i,
		DXGI_GPU_PREFERENCE_HIGH_PERFORMANCE, IID_PPV_ARGS(&useAdapter))
		!= DXGI_ERROR_NOT_FOUND; ++i) {

		DXGI_ADAPTER_DESC3 adapterDesc{};
		hr = useAdapter->GetDesc3(&adapterDesc);
		assert(SUCCEEDED(hr));
		//ソフトウェアアダプタでなければ採用！
		if (!(adapterDesc.Flags & DXGI_ADAPTER_FLAG3_SOFTWARE)) {
			//採用したアダプタの情報をログに出力
			Log(ConvertString(std::format(L"Use Adapater:{}\n", adapterDesc.Description)));
			break;
		}
		useAdapter = nullptr;
	}
	assert(useAdapter != nullptr);
	DxCommon::GetInstance()->dxgiFactory = dxgiFactory;
	DxCommon::GetInstance()->useAdapter = useAdapter;
	

}
/************************************************/
/***********   　よくわからない　   *************/
/************************************************/
void DxCommon::CreateFeneEvent()
{
	ID3D12Fence* fence = nullptr;//
	uint64_t fenceValue = 0;//
	HANDLE fenceEvent;//
	ID3D12Device* device = DxCommon::GetInstance()->device;
	///
	HRESULT hr = device->CreateFence(fenceValue, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&fence));
	assert(SUCCEEDED(hr));

	fenceEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
	assert(fenceEvent != nullptr);
	//
	DxCommon::GetInstance()->device = device;
	DxCommon::GetInstance()->fence = fence;
	DxCommon::GetInstance()->fenceValue = fenceValue;
	DxCommon::GetInstance()->fenceEvent = fenceEvent;

}
void DxCommon::CreateDevice()
{
	IDXGIAdapter4* useAdapter = DxCommon::GetInstance()->useAdapter;
	ID3D12Device* device = DxCommon::GetInstance()->device;
	///
	//D3D12Deviceの作成

	D3D_FEATURE_LEVEL featureLevels[] = {
			D3D_FEATURE_LEVEL_12_2,	D3D_FEATURE_LEVEL_12_1,	D3D_FEATURE_LEVEL_12_0
	};
	const char* featureLevelStrings[] = { "12.2","12.1","12.0" };
	for (size_t i = 0; i < _countof(featureLevels); ++i) {
		HRESULT hr = D3D12CreateDevice(useAdapter, featureLevels[i], IID_PPV_ARGS(&device));
		if (SUCCEEDED(hr)) {
			Log(std::format("FeatureLevel : {}\n", featureLevelStrings[i]));
			break;
		}
	}
	assert(device != nullptr);
	Log("Complete Create D3D12Device!!!\n");
	////
	DxCommon::GetInstance()->device = device;
	DxCommon::GetInstance()->useAdapter= useAdapter;
}
/************************************************/
/****************   　初期化　   ****************/
/************************************************/
void DxCommon::Initialize() {

	/* ----- デバッグレイヤー -----*/
#ifdef _DEBUG

	ID3D12Debug1* debugController = nullptr;

	if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&debugController)))) {
		// デバッグレイヤーを有効にする
		debugController->EnableDebugLayer();
		// さらにGPU側でもチェックを行うようにする
		debugController->SetEnableGPUBasedValidation(TRUE);
	}
	DxCommon::GetInstance()->debugController = debugController;
#endif // _DEBUG
	CreateDxgiFactory();
	CreateDevice();
	DebugInfoQueue();
	CreateCommands();

	CreateSwapChain();
	CreateDescriptorHeap();
	CreateFeneEvent();
}



void DxCommon::Release() {

	CloseHandle(DxCommon::GetInstance()->fenceEvent);
	DxCommon::GetInstance()->fence->Release();
	DxCommon::GetInstance()->rtvDescriptorHeap->Release();
	DxCommon::GetInstance()->swapChainResources[0]->Release();
	DxCommon::GetInstance()->swapChainResources[1]->Release();
	DxCommon::GetInstance()->swapChain->Release();
	DxCommon::GetInstance()->commandList->Release();
	DxCommon::GetInstance()->commandAllocator->Release();
	DxCommon::GetInstance()->commandQueue->Release();
	DxCommon::GetInstance()->device->Release();
	DxCommon::GetInstance()->useAdapter->Release();
	DxCommon::GetInstance()->dxgiFactory->Release();
#ifdef _DEBUG
	DxCommon::GetInstance()->debugController->Release();
#endif // _DEBUG

	CloseWindow(WinApp::GetInstance()->GetHwnd());

	//リソースリークチェック
	IDXGIDebug1* debug;
	if (SUCCEEDED(DXGIGetDebugInterface1(0, IID_PPV_ARGS(&debug)))) {
		debug->ReportLiveObjects(DXGI_DEBUG_ALL, DXGI_DEBUG_RLO_ALL);
		debug->ReportLiveObjects(DXGI_DEBUG_APP, DXGI_DEBUG_RLO_ALL);
		debug->ReportLiveObjects(DXGI_DEBUG_D3D12, DXGI_DEBUG_RLO_ALL);
		debug->Release();
	}
}
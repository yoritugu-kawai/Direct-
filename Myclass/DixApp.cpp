#include"DixApp.h"

std::wstring ConvertString(const std::string& str)
{
	if (str.empty())
	{
		return std::wstring();
	}

	auto sizeNeeded = MultiByteToWideChar(CP_UTF8, 0, reinterpret_cast<const char*>(&str[0]), static_cast<int>(str.size()), NULL, 0);
	if (sizeNeeded == 0)
	{
		return std::wstring();
	}
	std::wstring result(sizeNeeded, 0);
	MultiByteToWideChar(CP_UTF8, 0, reinterpret_cast<const char*>(&str[0]), static_cast<int>(str.size()), &result[0], sizeNeeded);
	return result;
}

std::string ConvertString(const std::wstring& str)
{
	if (str.empty())
	{
		return std::string();
	}

	auto sizeNeeded = WideCharToMultiByte(CP_UTF8, 0, str.data(), static_cast<int>(str.size()), NULL, 0, NULL, NULL);
	if (sizeNeeded == 0)
	{
		return std::string();
	}
	std::string result(sizeNeeded, 0);
	WideCharToMultiByte(CP_UTF8, 0, str.data(), static_cast<int>(str.size()), result.data(), sizeNeeded, NULL, NULL);
	return result;
}

void Log(const std::string& message) {
	OutputDebugStringA(message.c_str());
}

////コンパイルシェイダ
//IDxcBlob* CompileShader(
//	const std::wstring& filePath,
//	const wchar_t* profile,
//	IDxcUtils* dxcUtils,
//	IDxcCompiler3* dxcCompiler,
//	IDxcIncludeHandler* includeHandler)
//{
//	////_1
//	//Log(ConvertString(std::format(L"Begin CompileShader,path:{},profile:{}\n", filePath, profile)));
//	//IDxcBlobEncoding* shaderSource = nullptr;
//	//HRESULT hr = dxcUtils->LoadFile(filePath.c_str(), nullptr, &shaderSource);
//	//assert(SUCCEEDED(hr));
//	//DxcBuffer shaderSourceBuffer;
//	//shaderSourceBuffer.Ptr = shaderSource->GetBufferPointer();
//	//shaderSourceBuffer.Size = shaderSource->GetBufferSize();
//	//shaderSourceBuffer.Encoding = DXC_CP_UTF8;
//	////_2
//	//LPCWSTR arguments[] = {
//	//	filePath.c_str(),
//	//L"-E",L"main",
//	//L"-T",profile,
//	//L"-Zi",L"-Qembed_debug",
//	//L"-Od",
//	//L"-Zpr",
//	//};
//
//	//IDxcResult* shaderResult = nullptr;
//	//hr = dxcCompiler->Compile(
//	//	&shaderSourceBuffer,
//	//	arguments,
//	//	_countof(arguments),
//	//	includeHandler,
//	//	IID_PPV_ARGS(&shaderResult)
//
//	//);
//	//assert(SUCCEEDED(hr));
//	////_3
//	//IDxcBlobUtf8* shadeError = nullptr;
//	//shaderResult->GetOutput(DXC_OUT_ERRORS, IID_PPV_ARGS(&shadeError), nullptr);
//	//if (shadeError != nullptr && shadeError->GetStringLength() != 0) {
//	//	Log(shadeError->GetStringPointer());
//	//	assert(false);
//	//}
//	////_4
//	//IDxcBlob* shaderBlob = nullptr;
//	//hr = shaderResult->GetOutput(DXC_OUT_OBJECT, IID_PPV_ARGS(&shaderBlob), nullptr);
//	//assert(SUCCEEDED(hr));
//	//Log(ConvertString(std::format(L"Compile Shader,path:{},profile:{}\n", filePath, profile)));
//	//shaderSource->Release();
//	//shaderResult->Release();
//	//return  shaderBlob;
//}
//

/*DIXの初期設定*/
void DixApp::CreateFactory()
{
	//GXGFactoryの生成
	 dxgiFactory = nullptr;
	//HRESULTはWindows系のエラーコードあり
	//関数が成功したかどうかをSUCCEDEDマクロで判定できる
	 hr = CreateDXGIFactory(IID_PPV_ARGS(&dxgiFactory));

	//初期化の根本的な部分でエラーが出た場合はプログラムが間違っているか、どうにもできない場合が多いのでassertにしておく
	assert(SUCCEEDED(hr));

}
void DixApp::CreateAdapter() {
	//アダプタ決定
	 useAdapter = nullptr;
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
}
void DixApp::CreateDevice() {
	//D3D12Deviceの作成
	ID3D12Device* device = nullptr;
	D3D_FEATURE_LEVEL featureLevels[] = {
			D3D_FEATURE_LEVEL_12_2,	D3D_FEATURE_LEVEL_12_1,	D3D_FEATURE_LEVEL_12_0
	};
	const char* featureLevelStrings[] = { "12.2","12.1","12.0" };
	for (size_t i = 0; i < _countof(featureLevels); ++i) {
		hr = D3D12CreateDevice(useAdapter, featureLevels[i], IID_PPV_ARGS(&device));
		if (SUCCEEDED(hr)) {
			Log(std::format("FeatureLevel : {}\n", featureLevelStrings[i]));
			break;
		}
	}
	assert(device != nullptr);
	Log("Complete Create D3D12Device!!!\n");
}
/*DIXの初期設定*/

/*青画面*/
void DixApp::CreateCommandQueue() {

}
void DixApp::CreateCommandList() {

}

/*青画面*/

void DixApp::Initialize() {
	/*DIXの初期設定*/
	CreateFactory();
	CreateAdapter();
	CreateDevice();
	/*青画面*/
}


void  DixApp::POS() {

	///*---------ルートシグネチャの設定---------*/
	//D3D12_ROOT_SIGNATURE_DESC descriptionRootSignature{};
	//descriptionRootSignature.Flags = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;
	////シリアライズしてバイナリ


	//hr = D3D12SerializeRootSignature(&descriptionRootSignature,
	//	D3D_ROOT_SIGNATURE_VERSION_1, &signatureBlob, &errorBlob);
	//if (FAILED(hr)) {
	//	Log(reinterpret_cast<char*>(errorBlob->GetBufferPointer()));
	//	assert(false);
	//}
	////バイナリを元に生成

	//hr = device->CreateRootSignature(0, signatureBlob->GetBufferPointer(),
	//	signatureBlob->GetBufferSize(), IID_PPV_ARGS(&rootSignature));
	//assert(SUCCEEDED(hr));
	///*---------ルートシグネチャの設定---------*/

	///*----------インプットレイアウトの設定------------*/
	//D3D12_INPUT_ELEMENT_DESC inputElementDescs[1] = {};
	//inputElementDescs[0].SemanticName = "POSITION";
	//inputElementDescs[0].SemanticIndex = 0;
	//inputElementDescs[0].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	//inputElementDescs[0].AlignedByteOffset = D3D12_APPEND_ALIGNED_ELEMENT;
	//D3D12_INPUT_LAYOUT_DESC inputLayoutDesc{};
	//inputLayoutDesc.pInputElementDescs = inputElementDescs;
	//inputLayoutDesc.NumElements = _countof(inputElementDescs);

	///*------ブレンドステートの設定--------*/
	//D3D12_BLEND_DESC blendDesc{};
	//blendDesc.RenderTarget[0].RenderTargetWriteMask =
	//	D3D12_COLOR_WRITE_ENABLE_ALL;
	///*------ブレンドステートの設定--------*/

	///*-----ラスタライザステートの設定---*/
	//D3D12_RASTERIZER_DESC rasterizerDesc{};
	//rasterizerDesc.CullMode = D3D12_CULL_MODE_BACK;
	//rasterizerDesc.FillMode = D3D12_FILL_MODE_SOLID;
	///*-----ラスタライザステートの設定---*/

	///*-----シェイダ－コンパイル-------*/
	//vertexShaderBlob = CompileShader(L"Obiject3d.VS.hlsl",
	//	L"vs_6_0", dxcUtils, dxcCompiler, includeHandler);
	//assert(vertexShaderBlob != nullptr);

	//pixelShaderBlob = CompileShader(L"Odject3d.PS.hlsl",
	//	L"ps_6_0", dxcUtils, dxcCompiler, includeHandler);
	//assert(pixelShaderBlob != nullptr);
	///*-----シェイダ－コンパイル-------*/

	///*----POS作成--------*/

	//D3D12_GRAPHICS_PIPELINE_STATE_DESC graphicsPipelineStateDesc{};
	//graphicsPipelineStateDesc.pRootSignature = rootSignature;
	//graphicsPipelineStateDesc.InputLayout = inputLayoutDesc;
	//graphicsPipelineStateDesc.VS = { vertexShaderBlob->GetBufferPointer(),vertexShaderBlob->GetBufferSize() };
	//vertexShaderBlob->GetBufferSize();
	//graphicsPipelineStateDesc.PS = { pixelShaderBlob->GetBufferPointer(),pixelShaderBlob->GetBufferSize() };
	//pixelShaderBlob->GetBufferSize();
	//graphicsPipelineStateDesc.BlendState = blendDesc;
	//graphicsPipelineStateDesc.RasterizerState = rasterizerDesc;

	//graphicsPipelineStateDesc.NumRenderTargets = 1;
	//graphicsPipelineStateDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;

	//graphicsPipelineStateDesc.PrimitiveTopologyType =
	//	D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;

	//graphicsPipelineStateDesc.SampleDesc.Count = 1;
	//graphicsPipelineStateDesc.SampleMask = D3D12_DEFAULT_SAMPLE_MASK;


	//hr = device->CreateGraphicsPipelineState(&graphicsPipelineStateDesc,
	//	IID_PPV_ARGS(&graphicsPipelineState));
	//assert(SUCCEEDED(hr));
	///*----POS作成--------*/

	////////ⅤertexResource作成
	//D3D12_HEAP_PROPERTIES uploadHeapProperties{};
	//uploadHeapProperties.Type = D3D12_HEAP_TYPE_UPLOAD;

	//D3D12_RESOURCE_DESC vertexResourceDesc{};

	//vertexResourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	//vertexResourceDesc.Width = sizeof(Vector4) * 3;

	//vertexResourceDesc.Height = 1;
	//vertexResourceDesc.DepthOrArraySize = 1;
	//vertexResourceDesc.MipLevels = 1;
	//vertexResourceDesc.SampleDesc.Count = 1;

	//vertexResourceDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

	//hr = device->CreateCommittedResource(
	//	&uploadHeapProperties,
	//	D3D12_HEAP_FLAG_NONE,
	//	&vertexResourceDesc,
	//	D3D12_RESOURCE_STATE_GENERIC_READ,
	//	nullptr, IID_PPV_ARGS(&vertexResource));
	//assert(SUCCEEDED(hr));
}

void DixApp::Release(HWND hwnd) {

	//CloseHandle(fenceEvent);
	//fence->Release();
	//rtvDescriptorHeap->Release();
	//swapChainResources[0]->Release();
	//swapChainResources[1]->Release();
	//swapChain->Release();
	//commandList->Release();
	//commandAllocator->Release();
	//commandQueue->Release();
	//device->Release();
	//useAdapter->Release();
	//dxgiFactory->Release();

	//CloseWindow(hwnd);

	////リソースリークチェック
	//IDXGIDebug1* debug;
	//if (SUCCEEDED(DXGIGetDebugInterface1(0, IID_PPV_ARGS(&debug)))) {
	//	debug->ReportLiveObjects(DXGI_DEBUG_ALL, DXGI_DEBUG_RLO_ALL);
	//	debug->ReportLiveObjects(DXGI_DEBUG_APP, DXGI_DEBUG_RLO_ALL);
	//	debug->ReportLiveObjects(DXGI_DEBUG_D3D12, DXGI_DEBUG_RLO_ALL);
	//	debug->Release();
	//}

}
//void PolygonType::Initialize(Vector4 lefe, Vector4 top, Vector4 right)
//{
//	Vertex = CreateBufferResource(sizeof(VerteData) * 3);
//	materialResource = CreateBufferResource(sizeof(Vector4));
//	wvpResource = CreateBufferResource(sizeof(Matrix4x4));
//	bufferView_ = VertexCreateBufferView(sizeof(VerteData) * 3, Vertex, 3);
//
//	lefe_ = lefe,
//		top_ = top;
//	right_ = right;
//
//
//}
//
//
//void PolygonType::Draw(TexProeerty  tex, Matrix4x4 m, Vector4 Color)
//{
//	//色
//	Vector4* materialDeta = nullptr;
//	materialResource->Map(0, nullptr,
//		reinterpret_cast<void**>(&materialDeta));
//	*materialDeta = Color;
//	//移動
//	Matrix4x4* wvpData = nullptr;
//	wvpResource->Map(0, nullptr,
//		reinterpret_cast<void**>(&wvpData));
//	//*wvpData = MakeIdentity4x4();
//
//	/*transfom.rotate.y += speed;*/
//	/*Matrix4x4 worldMatrix = MakeAffineMatrix
//	(transfom.scale,
//		transfom.rotate,
//		transfom.translate);
//	*wvpData = worldMatrix;*/
//
//	//
//	VerteData* vertexData = nullptr;
//	Vertex->Map(0, nullptr,
//		reinterpret_cast<void**>(&vertexData));
//	////
//	//// 
//	//////射影
//
//	Matrix4x4 cameraMatrix = MakeAffineMatrix(cameratransform.scale, cameratransform.rotate, cameratransform.translate);
//	Matrix4x4 viewMatrix = Inverse(cameraMatrix);
//	Matrix4x4 projectionMatrix = MakePerspectiveFovMatrix(0.45f, float(WinApp::GetInstance()->Width()) / float(WinApp::GetInstance()->Height()), 0.1f, 100.0f);
//	Matrix4x4 worldViewProjectionMatrix = Multiply(m, Multiply(viewMatrix, projectionMatrix));
//	*wvpData = worldViewProjectionMatrix;
//
//
//	//座標
//	//左下
//	vertexData[0].position =
//	{ lefe_ };
//	vertexData[0].texcoord = { 0.0f,1.0f };
//	//上
//	vertexData[1].position =
//	{ top_ };
//	vertexData[1].texcoord = { 0.5f,0.0f };
//	//右下
//	vertexData[2].position =
//	{ right_ };
//	vertexData[2].texcoord = { 1.0f,1.0f };
//
//	//
//	PSOProperty pso_ = PipelineState::GetInstance()->GetPSO().shape;
//	ID3D12GraphicsCommandList* commandList = DxCommon::GetInstance()->GetCommandList();
//	commandList->SetGraphicsRootSignature(pso_.rootSignature);
//	commandList->SetPipelineState(pso_.GraphicsPipelineState);
//	commandList->IASetVertexBuffers(0, 1, &bufferView_);
//	commandList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
//	commandList->SetGraphicsRootConstantBufferView(0, materialResource->GetGPUVirtualAddress());
//	commandList->SetGraphicsRootConstantBufferView(1, wvpResource->GetGPUVirtualAddress());
//	commandList->SetGraphicsRootDescriptorTable(2, tex.SrvHandleGPU);
//	commandList->DrawInstanced(3, 1, 0, 0);
//}
//
//void PolygonType::Release()
//{
//	Vertex->Release();
//	materialResource->Release();
//	wvpResource->Release();
//}
//
//ID3D12Resource* PolygonType::CreateBufferResource(size_t sizeInbyte)
//{
//	ID3D12Device* device = DxCommon::GetInstance()->GetDevice();
//	ID3D12Resource* RssultResource;
//	//頂点リソース用のヒープの設定
//	D3D12_HEAP_PROPERTIES uploadHeapProperties{};
//
//	uploadHeapProperties.Type = D3D12_HEAP_TYPE_UPLOAD; //UploadHeapを使う
//
//	//頂点リソースの設定
//	D3D12_RESOURCE_DESC ResourceDesc{};
//
//	//バッファリソース。テクスチャの場合はまた別の設定をする
//	ResourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
//	ResourceDesc.Width = sizeInbyte; //リソースのサイズ。今回はvector4を3頂点分
//
//	//バッファの場合はこれらは1にする決まり
//	ResourceDesc.Height = 1;
//	ResourceDesc.DepthOrArraySize = 1;
//	ResourceDesc.MipLevels = 1;
//	ResourceDesc.SampleDesc.Count = 1;
//
//	//バッファの場合はこれにする決まり
//	ResourceDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
//	HRESULT hr;
//	hr = device->CreateCommittedResource(&uploadHeapProperties, D3D12_HEAP_FLAG_NONE,
//		&ResourceDesc, D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&RssultResource));
//	assert(SUCCEEDED(hr));
//
//	return RssultResource;
//}
//
//D3D12_VERTEX_BUFFER_VIEW PolygonType::VertexCreateBufferView(size_t sizeInbyte, ID3D12Resource* Resource, int size)
//{
//
//	D3D12_VERTEX_BUFFER_VIEW resultBufferView = {};
//
//	resultBufferView.BufferLocation = Resource->GetGPUVirtualAddress();
//
//	//使用するリソースのサイズは頂点3つ分のサイズ
//	resultBufferView.SizeInBytes = UINT(sizeInbyte);
//
//	//1頂点あたりのサイズ
//	resultBufferView.StrideInBytes = UINT(sizeInbyte / size);
//	return resultBufferView;
//}
///*/////////////////////////////////////////////////////////////////////////////////////////
//
//
//
//
//テキスト
//
//
//
//
//
//
/////////////////////////////////////////////////////////////////////////////////////////////////*/
//
//DirectX::ScratchImage Texture::LoadTexture(const std::string& filePath)
//{
//
//	//テクスチャファイルを読み込んでプログラムで扱えるようにする
//	DirectX::ScratchImage image{};
//	std::wstring filePathW = ConvertString(filePath);
//	HRESULT hr = DirectX::LoadFromWICFile(filePathW.c_str(), DirectX::WIC_FLAGS_FORCE_SRGB, nullptr, image);
//
//	assert(SUCCEEDED(hr));
//	//ミニマップの作成
//	DirectX::ScratchImage mipImage{};
//	hr = DirectX::GenerateMipMaps(image.GetImages(), image.GetImageCount(), image.GetMetadata(), DirectX::TEX_FILTER_SRGB, 0, mipImage);
//	assert(SUCCEEDED(hr));
//
//	//ミニマップ付きのデータを返す
//	return mipImage;
//
//}
//
//ID3D12Resource* Texture::CreateTexResource(ID3D12Device* device, const DirectX::TexMetadata& metadata)
//{
//	//1.metadataを基にResourceの設定
//	D3D12_RESOURCE_DESC resourceDesc{};
//	resourceDesc.Width = UINT(metadata.width);
//	resourceDesc.Height = UINT(metadata.height);
//	resourceDesc.MipLevels = UINT16(metadata.mipLevels);
//	resourceDesc.DepthOrArraySize = UINT16(metadata.arraySize);
//	resourceDesc.Format = metadata.format;
//	resourceDesc.SampleDesc.Count = 1;
//	resourceDesc.Dimension = D3D12_RESOURCE_DIMENSION(metadata.dimension);
//
//	//2.利用するHeapの設定。非常に特殊な運用。02_04exで一般的なケース版がある
//	D3D12_HEAP_PROPERTIES heapProperties{};
//	heapProperties.Type = D3D12_HEAP_TYPE_CUSTOM;
//	heapProperties.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_WRITE_BACK;
//	heapProperties.MemoryPoolPreference = D3D12_MEMORY_POOL_L0;
//
//
//	//3.Resourceを生成する
//	ID3D12Resource* resource = nullptr;
//	HRESULT hr = device->CreateCommittedResource(
//		&heapProperties,
//		D3D12_HEAP_FLAG_NONE,
//		&resourceDesc,
//		D3D12_RESOURCE_STATE_GENERIC_READ,
//		nullptr,
//		IID_PPV_ARGS(&resource));
//
//	assert(SUCCEEDED(hr));
//	return resource;
//}
//
//void Texture::UploadTexData(ID3D12Resource* texture, const DirectX::ScratchImage& mipImages)
//{
//	//Meta情報を取得
//	const DirectX::TexMetadata& metadata = mipImages.GetMetadata();
//
//	//全MipMapについて
//	for (size_t mipLevel = 0; mipLevel < metadata.mipLevels; ++mipLevel)
//	{
//		//MipMapLevelを指定して各Imagesを取得
//		const DirectX::Image* img = mipImages.GetImage(mipLevel, 0, 0);
//
//		//Textureに転送
//		HRESULT hr = texture->WriteToSubresource(
//			UINT(mipLevel),
//			nullptr, //全領域へコピー
//			img->pixels, //元データアドレス
//			UINT(img->rowPitch), //1ラインサイズ
//			UINT(img->slicePitch) //1枚サイズ
//		);
//
//		assert(SUCCEEDED(hr));
//	}
//
//}
//
//void Texture::ShaderResourceView()
//{
//
//
//}
//
//
//void Texture::Initiluze()
//{
//
//	CoInitializeEx(0, COINIT_MULTITHREADED);
//
//}
//
//TexProeerty  Texture::Load()
//{
//	ID3D12Device* device = DxCommon::GetInstance()->GetDevice();
//	ID3D12DescriptorHeap* srvDescriptorHeap = DxCommon::GetInstance()->GetsrvDescriptorHeap();
//	//Textureを読んで転送する
//	DirectX::ScratchImage mipImages = LoadTexture("resource/uvChecker.png");
//	const DirectX::TexMetadata& metadata = mipImages.GetMetadata();
//	ID3D12Resource* textureResource = CreateTexResource(device, metadata);
//	UploadTexData(textureResource, mipImages);
//
//	//テキストのシェダ－
//	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc{};
//	srvDesc.Format = metadata.format;
//	srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
//	srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
//	srvDesc.Texture2D.MipLevels = UINT(metadata.mipLevels);
//
//	D3D12_GPU_DESCRIPTOR_HANDLE texSrvHandleGPU = srvDescriptorHeap->GetGPUDescriptorHandleForHeapStart();
//	D3D12_CPU_DESCRIPTOR_HANDLE texSrvHandleCPU = srvDescriptorHeap->GetCPUDescriptorHandleForHeapStart();
//
//	texSrvHandleCPU.ptr += device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
//
//	texSrvHandleGPU.ptr += device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
//	device->CreateShaderResourceView(textureResource, &srvDesc, texSrvHandleCPU);
//	//
//
//	TexProeerty tex;
//	tex.Resource = textureResource;
//	tex.SrvHandleGPU = texSrvHandleGPU;
//	return tex;
//}
//
//void Texture::Draw()
//{
//}
//
//void Texture::End()
//{
//	CoUninitialize();
//}

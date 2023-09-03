#include "Polygon.h"

void PolygonType::Initialize(Vector4 pos, Vector4 Color)
{
	Vertex = CreateBufferResource(sizeof(VerteData) * 3);
	materialResource = CreateBufferResource(sizeof(Vector4));
	wvpResource = CreateBufferResource(sizeof(Matrix4x4));
	bufferView_ = VertexCreateBufferView(sizeof(VerteData) * 3, Vertex, 3);
	

	CenterPos_ = pos;
	Color_ = Color;

}


void PolygonType::Draw(TexProeerty  tex)
{
	//色
	Vector4* materialDeta = nullptr;
	materialResource->Map(0, nullptr,
		reinterpret_cast<void**>(&materialDeta));
	*materialDeta = Color_;
	//移動
	Matrix4x4* wvpData = nullptr;
	wvpResource->Map(0, nullptr, 
		reinterpret_cast<void**>(&wvpData));
	*wvpData = MakeIdentity4x4();

	transfom.rotate.y += 0.03f;
	Matrix4x4 worldMatrix = MakeAffineMatrix
	(transfom.scale, 
		transfom.rotate,
		transfom.translate);
	*wvpData = worldMatrix;
	
	//
	VerteData* vertexData = nullptr;
	Vertex->Map(0, nullptr,
		reinterpret_cast<void**>(&vertexData));
	//
	// 
	
	//座標
	//左下
	vertexData[0].position =
	{ CenterPos_.x - size,CenterPos_.y - size,CenterPos_.z,CenterPos_.w };
	vertexData[0].texcoord = { 0.0f,1.0f };
	//上
	vertexData[1].position = { CenterPos_.x,CenterPos_.y + size,CenterPos_.z,CenterPos_.w };
	vertexData[1].texcoord = { 0.5f,0.0f };
	//右上
	vertexData[2].position = { CenterPos_.x + size,CenterPos_.y - size,CenterPos_.z,CenterPos_.w };
	vertexData[2].texcoord = { 1.0f,1.0f };

	//
	PSOProperty pso_ = PipelineState::GetInstance()->GetPSO().shape;
	ID3D12GraphicsCommandList* commandList = DxCommon::GetInstance()->GetCommandList();
	commandList->SetGraphicsRootSignature(pso_.rootSignature);
	commandList->SetPipelineState(pso_.GraphicsPipelineState);
	commandList->IASetVertexBuffers(0, 1, &bufferView_);
	commandList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	commandList->SetGraphicsRootConstantBufferView(0, materialResource->GetGPUVirtualAddress());
	commandList->SetGraphicsRootConstantBufferView(1, wvpResource->GetGPUVirtualAddress());
	commandList->SetGraphicsRootDescriptorTable(2, tex.SrvHandleGPU);
	commandList->DrawInstanced(3, 1, 0, 0);
}

void PolygonType::Release()
{
	Vertex->Release();
	materialResource->Release();
	wvpResource->Release();
}

ID3D12Resource* PolygonType::CreateBufferResource(size_t sizeInbyte)
{
	ID3D12Device* device = DxCommon::GetInstance()->GetDevice();
	ID3D12Resource* RssultResource;
	//頂点リソース用のヒープの設定
	D3D12_HEAP_PROPERTIES uploadHeapProperties{};

	uploadHeapProperties.Type = D3D12_HEAP_TYPE_UPLOAD; //UploadHeapを使う

	//頂点リソースの設定
	D3D12_RESOURCE_DESC ResourceDesc{};

	//バッファリソース。テクスチャの場合はまた別の設定をする
	ResourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	ResourceDesc.Width = sizeInbyte; //リソースのサイズ。今回はvector4を3頂点分

	//バッファの場合はこれらは1にする決まり
	ResourceDesc.Height = 1;
	ResourceDesc.DepthOrArraySize = 1;
	ResourceDesc.MipLevels = 1;
	ResourceDesc.SampleDesc.Count = 1;

	//バッファの場合はこれにする決まり
	ResourceDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
	HRESULT hr;
	hr = device->CreateCommittedResource(&uploadHeapProperties, D3D12_HEAP_FLAG_NONE,
		&ResourceDesc, D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&RssultResource));
	assert(SUCCEEDED(hr));

	return RssultResource;
}

D3D12_VERTEX_BUFFER_VIEW PolygonType::VertexCreateBufferView(size_t sizeInbyte, ID3D12Resource* Resource, int size)
{

	D3D12_VERTEX_BUFFER_VIEW resultBufferView = {};

	resultBufferView.BufferLocation = Resource->GetGPUVirtualAddress();

	//使用するリソースのサイズは頂点3つ分のサイズ
	resultBufferView.SizeInBytes = UINT(sizeInbyte);

	//1頂点あたりのサイズ
	resultBufferView.StrideInBytes = UINT(sizeInbyte / size);
	return resultBufferView;
}

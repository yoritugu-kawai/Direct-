#include "Obj3D.h"

void Obj3D::Initialize(TexProeerty  tex)
{
	tex_ = tex;
	modelData = LoadObjFile("resource","axis.obj", tex_);


	vetexResource = CreateBufferResource(sizeof(VertexData) * modelData.vertices.size());
	materialResource = CreateBufferResource(sizeof(Vector4));
	wvpResource = CreateBufferResource(sizeof(TransformationMatrix));
	


	vertxBufferView.BufferLocation = vetexResource->GetGPUVirtualAddress();
	vertxBufferView.SizeInBytes = UINT(sizeof(VertexData) * modelData.vertices.size());
	vertxBufferView.StrideInBytes = sizeof(VertexData);


	
}

void Obj3D::Draw(Matrix4x4 m)
{

	//
	VertexData* vertexData = nullptr;
	Vector4* materialData = nullptr;
	TransformationMatrix* matrixData = nullptr;
	


	vetexResource->Map(0, nullptr, reinterpret_cast<void**>(&vertexData));
	materialResource->Map(0, nullptr, reinterpret_cast<void**>(&materialData));
	wvpResource->Map(0, nullptr, reinterpret_cast<void**>(&matrixData));

	std::memcpy(vertexData, modelData.vertices.data(), sizeof(VertexData)*
		modelData.vertices.size());
	//
	// 

	matrixData->WVP = m;
	matrixData->World = MakeIdentity4x4();
	*materialData = { 1,1,1,1 };


	//
	ID3D12GraphicsCommandList* commandList = DxCommon::GetInstance()->GetCommandList();
	PSOProperty pso_ = TexturePSO::GetInstance()->GetPSO().Texture;
	commandList->SetGraphicsRootSignature(pso_.rootSignature);
	commandList->SetPipelineState(pso_.GraphicsPipelineState);

	commandList->IASetVertexBuffers(0, 1, &vertxBufferView);

	commandList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	commandList->SetGraphicsRootConstantBufferView(0, materialResource->GetGPUVirtualAddress());

	commandList->SetGraphicsRootDescriptorTable(2, tex_.SrvHandleGPU);
	commandList->SetGraphicsRootConstantBufferView(1, wvpResource->GetGPUVirtualAddress());

	commandList->DrawInstanced(UINT(modelData.vertices.size()), 1, 0, 0);
}

void Obj3D::Release()
{
	vetexResource->Release();
	materialResource->Release();
	wvpResource->Release();
	tex_.Resource->Release();

}

ID3D12Resource* Obj3D::CreateBufferResource(size_t sizeInbyte)
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
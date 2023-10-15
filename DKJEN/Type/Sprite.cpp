#include "Sprite.h"

void Sprite::Initialize()
{
	vertexResourceSprite = CreateBufferResource(sizeof(VerteData) * 6);
	transformationMatrixResourceSprote = CreateBufferResource(sizeof(Matrix4x4));
}

void Sprite::Vertex()
{

	vertexBufferViewSprite.BufferLocation = vertexResourceSprite->GetGPUVirtualAddress();
	vertexBufferViewSprite.SizeInBytes = sizeof(VerteData) * 6;
	vertexBufferViewSprite.StrideInBytes = sizeof(VerteData);
	//頂点データ

	
	vertexResourceSprite->Map(0, nullptr, reinterpret_cast<void**>(&VertexDataSprite));
	//1枚目
	//左下
	VertexDataSprite[0].position = { 0.0f,360.0f,0.0f,1.0f };
	VertexDataSprite[0].texcoord = { 0.0f,1.0f };
	//左上
	VertexDataSprite[1].position = { 0.0f,0.0f,0.0f,1.0f };
	VertexDataSprite[1].texcoord = { 0.0f,0.0f };
	//右下
	VertexDataSprite[2].position = { 640.0f,360.0f,0.0f,1.0f };
	VertexDataSprite[2].texcoord = { 1.0f,1.0f };
	//二枚目
	//左上
	VertexDataSprite[3].position = { 0.0f,0.0f,0.0f,1.0f };
	VertexDataSprite[3].texcoord = { 0.0f,0.0f };
	//右上
	VertexDataSprite[4].position = { 640.f,0.0f,0.0f,1.0f };
	VertexDataSprite[4].texcoord = { 1.0f,0.0f };
	//右下
	VertexDataSprite[5].position = { 640.0f,360.0f,0.0f,1.0f };
	VertexDataSprite[5].texcoord = { 1.0f,1.0f };


}
void Sprite::Darw()
{
	Vertex();



	transformationMatrixResourceSprote->Map(0, nullptr, reinterpret_cast<void**>
		(&transformationMatrixDataSprite));
	*transformationMatrixDataSprite = MakeIdentity4x4();
	
	Matrix4x4 SpriteMatrix = MakeAffineMatrix(transformSprite.scale, transformSprite.rotate, transformSprite.translate);
	Matrix4x4 viewMatrix = MakeIdentity4x4();
	Matrix4x4 projectionMatrix = MakeOrthographicMatrix(0.0f, 0.0f, float(WinApp::GetInstance()->Width()) ,float(WinApp::GetInstance()->Height()), 0.0f, 100.0f);
	Matrix4x4 worldViewProjectionMatrix = Multiply(SpriteMatrix, Multiply(viewMatrix, projectionMatrix));
	*transformationMatrixDataSprite = worldViewProjectionMatrix;


	//
	ID3D12GraphicsCommandList* commandList = DxCommon::GetInstance()->GetCommandList();

	commandList->IASetVertexBuffers(0, 1, &vertexBufferViewSprite);

	
	

    commandList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
   // commandList->SetGraphicsRootConstantBufferView(0, materialResource_->GetGPUVirtualAddress());

	commandList->SetGraphicsRootConstantBufferView(1, transformationMatrixResourceSprote->GetGPUVirtualAddress());
   
    
	//commandList->SetGraphicsRootDescriptorTable(2, textureManager->GetTextureSrvHandleGPU());

	
	
	commandList->DrawInstanced(6, 1, 0, 0);

}

void Sprite::Release()
{
	vertexResourceSprite->Release();
	transformationMatrixResourceSprote->Release();
	
}

ID3D12Resource* Sprite::CreateBufferResource(size_t sizeInbyte)
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
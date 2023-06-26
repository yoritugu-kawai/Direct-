#include"Polygon.h"

PolygoType::PolygoType()
{
}

PolygoType::~PolygoType()
{
}

void PolygoType::Initiluze(DxCommon* dxcommon)
{
	dxcommon_ = dxcommon;
}

void PolygoType::Update(int32_t  kClientWidth, int32_t kClientHeight)
{


	//描画許可範囲

	scissorRect.left = 0;
	scissorRect.right = kClientWidth;
	scissorRect.top = 0;
	scissorRect.bottom = kClientHeight;
	//表示許可範囲

//
	viewport.Width = float(kClientWidth);
	viewport.Height = float(kClientHeight);
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;

	dxcommon_->commandListGet()->RSSetViewports(1, &viewport);
	dxcommon_->commandListGet()->RSSetScissorRects(1, &scissorRect);

}

BufferResource PolygoType::CreateBufferResource()
{

	//////ⅤertexResource作成
	D3D12_HEAP_PROPERTIES uploadHeapProperties{};
	uploadHeapProperties.Type = D3D12_HEAP_TYPE_UPLOAD;

	D3D12_RESOURCE_DESC vertexResourceDesc{};

	vertexResourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	vertexResourceDesc.Width = sizeof(Vector4) * 3;

	vertexResourceDesc.Height = 1;
	vertexResourceDesc.DepthOrArraySize = 1;
	vertexResourceDesc.MipLevels = 1;
	vertexResourceDesc.SampleDesc.Count = 1;

	vertexResourceDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

	BufferResource bufferResource;


	HRESULT hr = dxcommon_->deviceGet()->CreateCommittedResource(
		&uploadHeapProperties,
		D3D12_HEAP_FLAG_NONE,
		&vertexResourceDesc,
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr, IID_PPV_ARGS(&bufferResource.vertexResource));
	assert(SUCCEEDED(hr));


	//VerteBufferView作成

	bufferResource.vertexBufferView.BufferLocation = bufferResource.vertexResource->GetGPUVirtualAddress();
	bufferResource.vertexBufferView.SizeInBytes = sizeof(Vector4) * 3;

	bufferResource.vertexBufferView.StrideInBytes = sizeof(Vector4);

	return bufferResource;
}

void PolygoType::Triangle(Vector4 lefe, Vector4 top, Vector4 right, ID3D12Resource* vertexResource)
{
	Vector4* vertexData = nullptr;
	vertexResource->Map(0, nullptr, reinterpret_cast<void**>(&vertexData));
	vertexData[0] = { lefe };
	vertexData[1] = { top };
	vertexData[2] = { right };


}

void PolygoType::Call(BufferResource bufferResource)
{

	//コマンドつむ２

	dxcommon_->commandListGet()->SetGraphicsRootSignature(dxcommon_->rootSignatureGet());
	dxcommon_->commandListGet()->SetPipelineState(dxcommon_->graphicsPipelineStateGet());
	dxcommon_->commandListGet()->IASetVertexBuffers(0, 1, &bufferResource.vertexBufferView);
	dxcommon_->commandListGet()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	dxcommon_->commandListGet()->DrawInstanced(3, 1, 0, 0);

}
void PolygoType::Draw(Vector4 lefe, Vector4 top, Vector4 right, ID3D12Resource* vertexResource, BufferResource bufferResource)
{
	Triangle(lefe, top, right, bufferResource.vertexResource);
	Call(bufferResource);

}

//void PolygoType::Release( IDxcBlob* pixelShaderBlob, IDxcBlob* vertexShaderBlob, ID3DBlob* signatureBlob, ID3DBlob* errorBlob, ID3D12Resource* vertexResource)
//{
//	vertexResource->Release();
//	graphicsPipelineState->Release();
//	signatureBlob->Release();
//	if (errorBlob) {
//		errorBlob->Release();
//
//	}
//	dxcommon_->rootSignatureGet()->Release();
//	pixelShaderBlob->Release();
//	vertexShaderBlob->Release();
//
//}


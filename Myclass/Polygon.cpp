#include"Polygon.h"

PolygoType::PolygoType()
{
}

PolygoType::~PolygoType()
{
}

void PolygoType::Initiluze(DxCommon* dxcommon, int32_t  kClientWidth, int32_t kClientHeight, Vector4 lefe, Vector4 top, Vector4 right)
{
	dxcommon_ = dxcommon;
	this->kClientWidth_ = kClientWidth;
	this->kClientHeight_ = kClientHeight;
	this->lefe_= lefe,
	this->top_= top;
	this->right_= right;
}

void PolygoType::Update()
{


}

void PolygoType::CreateBufferResource()
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

	HRESULT hr = dxcommon_->deviceGet()->CreateCommittedResource(&uploadHeapProperties ,
		D3D12_HEAP_FLAG_NONE,
		&vertexResourceDesc, 
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&vertexResource));
	assert(SUCCEEDED(hr));

	//VerteBufferView作成

	vertexBufferView.BufferLocation = vertexResource->GetGPUVirtualAddress();
	vertexBufferView.SizeInBytes = sizeof(Vector4) * 3;

    vertexBufferView.StrideInBytes = sizeof(Vector4);
}

void PolygoType::Draw()
{
	//描画許可範囲
	scissorRect.left = 0;
	scissorRect.right = kClientWidth_;
	scissorRect.top = 0;
	scissorRect.bottom = kClientHeight_;
	//表示許可範囲
	viewport.Width = float(kClientWidth_);
	viewport.Height = float(kClientHeight_);
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;

	CreateBufferResource();

	Vector4* vertexData = nullptr;
	vertexResource->Map(0, nullptr, reinterpret_cast<void**>(&vertexData));
	vertexData[0] = { lefe_ };
	vertexData[1] = { top_ };
	vertexData[2] = { right_ };

	//コマンドつむ２
	dxcommon_->commandListGet()->RSSetViewports(1, &viewport);
	dxcommon_->commandListGet()->RSSetScissorRects(1, &scissorRect);
	dxcommon_->commandListGet()->SetGraphicsRootSignature(dxcommon_->rootSignatureGet());
	dxcommon_->commandListGet()->SetPipelineState(dxcommon_->graphicsPipelineStateGet());
	dxcommon_->commandListGet()->IASetVertexBuffers(0, 1, &vertexBufferView);
	dxcommon_->commandListGet()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	dxcommon_->commandListGet()->DrawInstanced(3, 1, 0, 0);

}

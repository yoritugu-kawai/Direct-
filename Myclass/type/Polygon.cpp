#include"Polygon.h"

PolygoType::PolygoType()
{
}

PolygoType::~PolygoType()
{
}

Vector4 PolygoType::Color(unsigned int color)
{
	Vector4 color_ = {
			((color >> 24) & 0xff) / 255.0f, // R
			((color >> 16) & 0xff) / 255.0f, // G
			((color >> 8) & 0xff) / 255.0f,  // B
			((color >> 0) & 0xff) / 255.0f   // A
	};

	return color_;
}


void PolygoType::Initiluze(DxCommon* dxcommon)
{
	dxcommon_ = dxcommon;
	vertexResource = CreateBufferResource(dxcommon_->deviceGet(), sizeof(Vector4) * 3);
	materialResource = CreateBufferResource(dxcommon_->deviceGet(), sizeof(Vector4)* 3);
	wvpResource = CreateBufferResource(dxcommon_->deviceGet(), sizeof(Vector4) * 3);
	vertexBufferView.BufferLocation = vertexResource->GetGPUVirtualAddress();
	vertexBufferView.SizeInBytes = sizeof(Vector4) * 3;

	vertexBufferView.StrideInBytes = sizeof(Vector4);

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

void PolygoType::Move()
{
	
}

ID3D12Resource* PolygoType::CreateBufferResource(ID3D12Device* device, size_t sizeInBytes)
{
	ID3D12Resource* resultResource_;
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


	HRESULT hr =  device ->CreateCommittedResource(&uploadHeapProperties,
		D3D12_HEAP_FLAG_NONE,
		&vertexResourceDesc,
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&resultResource_));
	assert(SUCCEEDED(hr));

	//VerteBufferView作成

	return resultResource_;
}

void PolygoType::Triangle(Vector4 lefe, Vector4 top, Vector4 right, unsigned int color)
{
	//PS
	Vector4* materialData = nullptr;
	materialResource->Map(0, nullptr, reinterpret_cast<void**>(&materialData));
	*materialData = Color(color);
	//VS
	Matrix4x4* wvpData = nullptr;
	wvpResource->Map(0, nullptr, reinterpret_cast<void**>(&wvpData));
	//*wvpData = MakeIdentity4x4();

	transfom.rotate.y += 0.03f;
	Matrix4x4 worldMatrix = MakeAffineMatrix(transfom.scale, transfom.rotate, transfom.translate);
	*wvpData = worldMatrix;

	//TR
	Vector4* vertexData = nullptr;
	vertexResource->Map(0, nullptr, reinterpret_cast<void**>(&vertexData));
	vertexData[0] = { lefe };
	vertexData[1] = { top };
	vertexData[2] = { right };

	
}

void PolygoType::Call()
{

	//コマンドつむ２

	dxcommon_->commandListGet()->SetGraphicsRootSignature(dxcommon_->rootSignatureGet());
	dxcommon_->commandListGet()->SetGraphicsRootConstantBufferView(1, wvpResource->GetGPUVirtualAddress());
	dxcommon_->commandListGet()->SetPipelineState(dxcommon_->graphicsPipelineStateGet());
	dxcommon_->commandListGet()->IASetVertexBuffers(0, 1, &vertexBufferView);
	dxcommon_->commandListGet()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	dxcommon_->commandListGet()->SetGraphicsRootConstantBufferView(0, materialResource->GetGPUVirtualAddress());
	dxcommon_->commandListGet()->DrawInstanced(3, 1, 0, 0);
	
}
void PolygoType::Draw(Vector4 lefe, Vector4 top, Vector4 right, unsigned int color)
{
	Triangle(lefe, top, right, color);
	Call();

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

#include"Polygon.h"

PolygonApp::PolygonApp()
{
}

PolygonApp::~PolygonApp()
{
}



void PolygonApp::Initialize(int32_t  kClientWidth, int32_t kClientHeight, ID3D12GraphicsCommandList* commandList)
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
	
	commandList->RSSetViewports(1, &viewport);
	commandList->RSSetScissorRects(1, &scissorRect);

}

BufferResource PolygonApp::CreateBufferResource( ID3D12Device* device)
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
	
	
	HRESULT hr = device->CreateCommittedResource(
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

void PolygonApp::Triangle(Vector4 lefe,Vector4 top , Vector4 right, ID3D12Resource* vertexResource)
{
	Vector4* vertexData = nullptr;
	vertexResource->Map(0, nullptr, reinterpret_cast<void**>(&vertexData));
	vertexData[0] = {lefe};
	vertexData[1] = { top};
	vertexData[2] = { right};
	
	
}

void PolygonApp::Call(ID3D12GraphicsCommandList* commandList, ID3D12RootSignature* rootSignature, ID3D12PipelineState* graphicsPipelineState, BufferResource bufferResource )
{
	
	//コマンドつむ２

	commandList->SetGraphicsRootSignature(rootSignature);
	commandList->SetPipelineState(graphicsPipelineState);
	commandList->IASetVertexBuffers(0, 1, &bufferResource.vertexBufferView);

	commandList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	commandList->DrawInstanced(3, 1, 0, 0);

}
void PolygonApp::Draw(Vector4 lefe, Vector4 top, Vector4 right, ID3D12GraphicsCommandList* commandList, ID3D12RootSignature* rootSignature, ID3D12PipelineState* graphicsPipelineState, ID3D12Resource* vertexResource, BufferResource bufferResource)
{
	Triangle(lefe,  top, right,  bufferResource.vertexResource);
	Call( commandList,  rootSignature, graphicsPipelineState, bufferResource);
	
}

void PolygonApp::Release(ID3D12RootSignature* rootSignature, ID3D12PipelineState* graphicsPipelineState, IDxcBlob* pixelShaderBlob, IDxcBlob* vertexShaderBlob, ID3DBlob* signatureBlob, ID3DBlob* errorBlob, ID3D12Resource* vertexResource)
{
	vertexResource->Release();
	graphicsPipelineState->Release();
	signatureBlob->Release();
	if (errorBlob) {
		errorBlob->Release();

	}
	rootSignature->Release();
	pixelShaderBlob->Release();
	vertexShaderBlob->Release();

}


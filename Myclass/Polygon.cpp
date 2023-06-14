//#include"Polygon.h"
//
//PolygonApp::PolygonApp()
//{
//}
//
//PolygonApp::~PolygonApp()
//{
//}
//
//
//
//void PolygonApp::Initialize(int32_t  kClientWidth, int32_t kClientHeight,  ID3D12Device* device)
//{
//
//	//////ⅤertexResource作成
//	D3D12_HEAP_PROPERTIES uploadHeapProperties{};
//	uploadHeapProperties.Type = D3D12_HEAP_TYPE_UPLOAD;
//
//	D3D12_RESOURCE_DESC vertexResourceDesc{};
//
//	vertexResourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
//	vertexResourceDesc.Width = sizeof(Vector4) * 3;
//
//	vertexResourceDesc.Height = 1;
//	vertexResourceDesc.DepthOrArraySize = 1;
//	vertexResourceDesc.MipLevels = 1;
//	vertexResourceDesc.SampleDesc.Count = 1;
//
//	vertexResourceDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
//	
//	hr = device->CreateCommittedResource(
//		&uploadHeapProperties,
//		D3D12_HEAP_FLAG_NONE,
//		&vertexResourceDesc,
//		D3D12_RESOURCE_STATE_GENERIC_READ,
//		nullptr, IID_PPV_ARGS(&vertexResource));
//	assert(SUCCEEDED(hr));
//
//
//
//	D3D12_RECT scissorRect{};
//
//	scissorRect.left = 0;
//	scissorRect.right = kClientWidth;
//	scissorRect.top = 0;
//	scissorRect.bottom = kClientHeight;
//
//
//}
//
//void PolygonApp::Triangle(float width,float  height,float x,float y)
//{
//	//VerteBufferView作成
//	
//	vertexBufferView.BufferLocation = vertexResource->GetGPUVirtualAddress();
//	vertexBufferView.SizeInBytes = sizeof(Vector4) * 3;
//
//	vertexBufferView.StrideInBytes = sizeof(Vector4);
//
//
//
//	Vector4* vertexData = nullptr;
//	vertexResource->Map(0, nullptr, reinterpret_cast<void**>(&vertexData));
//	vertexData[0] = {
//		-0.5f,
//		-0.5f,
//		0.0f,
//		1.0f };
//	vertexData[1] = { 0.0f,
//		0.5f,
//		0.0f,
//		1.0f };
//	vertexData[2] = { 0.5f,
//		-0.5f,
//		0.0f,
//		1.0f };
//
//	//ビューボード
//	
//
//	viewport.Width = width;
//	viewport.Height = height;
//	viewport.TopLeftX = x;
//	viewport.TopLeftY = y;
//	viewport.MinDepth = 0.0f;
//	viewport.MaxDepth = 1.0f;
//
//}
//
//void PolygonApp::DrawCall(ID3D12CommandList *commandList)
//{
//	//コマンドを積む
//	commandList->RSSetViewports(1, &viewport);
//	commandList->RSSetScissorRects(1, &scissorRect);
//
//	commandList->SetGraphicsRootSignature(dixApp->rootSignature);
//	commandList->SetPipelineState(dixApp->graphicsPipelineState);
//	commandList->IASetVertexBuffers(0, 1, &vertexBufferView);
//
//	commandList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
//
//	commandList->DrawInstanced(3, 1, 0, 0);
//}
//
//void PolygonApp::Release()
//{
//	vertexResource->Release();
//	dixApp->graphicsPipelineState->Release();
//
//	dixApp->rootSignature->Release();
//	
//}

#include"Sphere.h"

void Sphere::Initialize(Vector4 pos, float size)
{
	const uint32_t v = VertexNum_ * VertexNum_ * 6;
	Vertex = CreateBufferResource(sizeof(VerteData) * v);
	wvpResource = CreateBufferResource(sizeof(Matrix4x4));
	bufferView_ = VertexCreateBufferView(sizeof(VerteData) * v, Vertex, v);
	materialResource = CreateBufferResource(sizeof(Vector4));
	centerPos_ = pos;
	radious_ = size;

	Roadtex_->Initiluze();
	tex_ = Roadtex_->Load();
	viewMatrix.m[3][2] = 2;
}

void Sphere::Draw(Matrix4x4 m)
{
	VerteData* vertexData = nullptr;
	Vector4* MaterialData = nullptr;
	Matrix4x4* wvpData = nullptr;

	


	//書き込むためのアドレスを取得
	Vertex->Map(0, nullptr, reinterpret_cast<void**>(&vertexData));
	materialResource->Map(0, nullptr, reinterpret_cast<void**>(&MaterialData));

	wvpResource->Map(0, nullptr, reinterpret_cast<void**>(&wvpData));

	const float LON_EVERY = float(std::numbers::pi) * 2.0f / float(VertexNum_);
	//緯度分割1つ分の角度θd
	const float LAT_EVERY = float(std::numbers::pi) / float(VertexNum_);
	{
		//緯度の方向に分割
		for (int latIndex = 0; latIndex < VertexNum_; ++latIndex) {
			//θ
			float lat = -float(std::numbers::pi) / 2.0f + LAT_EVERY * latIndex;
			//経度の方向に分割しながら線を描く
			for (int lonIndex = 0; lonIndex < VertexNum_; ++lonIndex) {
				uint32_t start = (latIndex * VertexNum_ + lonIndex) * 6;

				//texcoord専用のxy座標
				float u = float(lonIndex) / float(VertexNum_);
				//下から0上が1になっていたので「1.0f-～」にして逆にする
				float v = 1.0f - float(latIndex) / float(VertexNum_);

				float lon = lonIndex * LON_EVERY;
				//頂点にデータを入力する。基準点a
				//点間の距離
				float length = 1.0f / VertexNum_;

#pragma region 三角形１枚目 
				//左上(点B)が原点
				//abc
				//資料通りだとここは点a(左下)
				vertexData[start].position.x = radious_ * (cos(lat) * cos(lon));
				vertexData[start].position.y = radious_ * (sin(lat));
				vertexData[start].position.z = radious_ * (cos(lat) * sin(lon));
				vertexData[start].position.w = 1.0f;
				//分割分移動
				vertexData[start].texcoord.x = u;
				vertexData[start].texcoord.y = v + length;

				//点b(左上)
				vertexData[start + 1].position.x = radious_ * (cos(lat + LAT_EVERY)) * cos(lon);
				vertexData[start + 1].position.y = radious_ * (sin(lat + LAT_EVERY));
				vertexData[start + 1].position.z = radious_ * (cos(lat + LAT_EVERY)) * sin(lon);
				vertexData[start + 1].position.w = 1.0f;
				vertexData[start + 1].texcoord.x = u;
				vertexData[start + 1].texcoord.y = v;


				//点c(右下)
				vertexData[start + 2].position.x = radious_ * (cos(lat) * cos(lon + LON_EVERY));
				vertexData[start + 2].position.y = radious_ * (sin(lat));
				vertexData[start + 2].position.z = radious_ * (cos(lat) * sin(lon + LON_EVERY));
				vertexData[start + 2].position.w = 1.0f;
				vertexData[start + 2].texcoord.x = u + length;
				vertexData[start + 2].texcoord.y = v + length;

#pragma endregion

#pragma region 三角形２枚目
				//bcd
				//点d(右上)
				vertexData[start + 3].position.x = radious_ * (cos(lat + LAT_EVERY) * cos(lon + LON_EVERY));
				vertexData[start + 3].position.y = radious_ * (sin(lat + LAT_EVERY));
				vertexData[start + 3].position.z = radious_ * (cos(lat + LAT_EVERY) * sin(lon + LON_EVERY));
				vertexData[start + 3].position.w = 1.0f;
				vertexData[start + 3].texcoord.x = u + length;
				vertexData[start + 3].texcoord.y = v;

				//点c(右下)
				vertexData[start + 4].position.x = radious_ * (cos(lat) * cos(lon + LON_EVERY));
				vertexData[start + 4].position.y = radious_ * (sin(lat));
				vertexData[start + 4].position.z = radious_ * (cos(lat) * sin(lon + LON_EVERY));
				vertexData[start + 4].position.w = 1.0f;
				vertexData[start + 4].texcoord.x = u + length;
				vertexData[start + 4].texcoord.y = v + length;



				//点b(左上)
				vertexData[start + 5].position.x = radious_ * (cos(lat + LAT_EVERY) * cos(lon));
				vertexData[start + 5].position.y = radious_ * (sin(lat + LAT_EVERY));
				vertexData[start + 5].position.z = radious_ * (cos(lat + LAT_EVERY) * sin(lon));
				vertexData[start + 5].position.w = 1.0f;
				vertexData[start + 5].texcoord.x = u;
				vertexData[start + 5].texcoord.y = v;
#pragma endregion
			}
		}
	}

	ImGui::Begin("SphereCamera");
	ImGui::DragFloat("CameraZ", &viewMatrix.m[3][2], 2);
	ImGui::Checkbox("useMonsterBall", &useMonsterBall);
	ImGui::End();
	Matrix4x4 projectionMatrix = MakePerspectiveFovMatrix(0.45f, float(WinApp::GetInstance()->Width()) / float(WinApp::GetInstance()->Height()), 0.1f, 100.0f);

    Matrix4x4 worldViewProjectionMatrix = Multiply(m, Multiply(viewMatrix, projectionMatrix));

	*wvpData = worldViewProjectionMatrix;

	//*wvpData = m;

	*MaterialData = color_;

	CommandCall();
}

void Sphere::Release()
{
	Vertex->Release();
	materialResource->Release();
	wvpResource->Release();
	tex_.Resource->Release();
	tex_.Resource2->Release();
	
}

void Sphere::CommandCall()
{
	ID3D12GraphicsCommandList* commandList = DxCommon::GetInstance()->GetCommandList();
	PSOProperty pso_ = SpritePSO::GetInstance()->GetPSO().Texture;


	commandList->SetGraphicsRootSignature(pso_.rootSignature);
	commandList->SetPipelineState(pso_.GraphicsPipelineState);//

	commandList->IASetVertexBuffers(0, 1, &bufferView_);

	
	commandList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	commandList->SetGraphicsRootConstantBufferView(1,wvpResource->GetGPUVirtualAddress());
	commandList->SetGraphicsRootConstantBufferView(0, materialResource->GetGPUVirtualAddress());
	//commandList->SetGraphicsRootConstantBufferView(1, transformationMatrixResource->GetGPUVirtualAddress());
	//
	commandList->SetGraphicsRootDescriptorTable(2, useMonsterBall ? tex_.SrvHandleGPU2: tex_.SrvHandleGPU);


	//描画(DrawCall/ドローコール)。
	commandList->DrawInstanced(VertexNum_ * VertexNum_ * 6, 1, 0, 0);

}



ID3D12Resource* Sphere::CreateBufferResource(size_t sizeInbyte)
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

D3D12_VERTEX_BUFFER_VIEW Sphere::VertexCreateBufferView(size_t sizeInbyte, ID3D12Resource* Resource, int size)
{

	D3D12_VERTEX_BUFFER_VIEW resultBufferView = {};

	resultBufferView.BufferLocation = Resource->GetGPUVirtualAddress();

	//使用するリソースのサイズは頂点3つ分のサイズ
	resultBufferView.SizeInBytes = UINT(sizeInbyte);

	//1頂点あたりのサイズ
	resultBufferView.StrideInBytes = UINT(sizeInbyte / size);
	return resultBufferView;
}

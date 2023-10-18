#pragma once
#pragma once
#include"../Base/WinApp.h"
#include"../Base/DxCommon.h"
#include"../Base/Function.h"
#include"../externals/DirectXTex/d3dx12.h"
#include"../externals/DirectXTex/DirectXTex.h"
struct VerteData {
	Vector4 position;
	Vector2 texcoord;
};
struct TexProeerty {
	D3D12_GPU_DESCRIPTOR_HANDLE SrvHandleGPU;
	D3D12_GPU_DESCRIPTOR_HANDLE SrvHandleGPU2;
	ID3D12Resource* Resource;
	ID3D12Resource* Resource2;

};

class RoadTexture
{
public:
	void Initiluze();
	TexProeerty Load();
	//void Draw();
	void End();
	DirectX::ScratchImage LoadTexture(const std::string& filePath);
	ID3D12Resource* CreateTexResource(ID3D12Device* device, const DirectX::TexMetadata& metadata);
	void UploadTexData(ID3D12Resource* texture, const DirectX::ScratchImage& mipImages);
	void ShaderResourceView();
private:
	DxCommon dxcommon_;

	uint32_t descriptorSizeSRV;
	uint32_t descriptorSizeRTV;
	uint32_t descriptorSizeDSV;

};

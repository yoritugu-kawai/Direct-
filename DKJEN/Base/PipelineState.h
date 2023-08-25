#pragma once
#include"DxCommon.h"
#include"../Shader/CompileShader.h"
struct PSOProperty
{
	ID3D12PipelineState* GraphicsPipelineState = nullptr;
	ID3D12RootSignature* rootSignature = nullptr;
	ID3DBlob* signatureBlob = nullptr;
	ID3DBlob* errorBlob = nullptr;

};
struct PSO
{
	PSOProperty shape;
	

};
class PipelineState
{
public:
	static PipelineState* GetInstance();
	
	//PSO
	
	static void CreatePSO();
	static void Release();
	static PSO GetPSO() {return PipelineState::GetInstance()->pso_;}
private:
	//
	static void ShapePSO();
	HRESULT hr;//
	
	PSO pso_;
};

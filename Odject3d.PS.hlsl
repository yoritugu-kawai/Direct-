//float4 main( float4 pos : POSITION ) : SV_POSITION
//{
//	
//	return pos;
//}

struct Material {
	float32_t4 color;

};
/*---------*/
//RootSignature作成
//ConstantBuffer<Material>gMaterial:register(b0);
//D3D12_ROOT_SIGNATURE_DESC descriptionRootSignature{};
//descriptionRootSignature.Flags = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;
//
////
//D3D12ROOT_PARAMETER rootParameters[1] = {};
//rootParameters[0].ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;
//rootParameters[0].ShadeVisibility = D3D12_SHADER_VISIBILITY_PIXEL;
//rootParameters[0].Deacriptor.ShaderRegister = 0;
//descriptionRootSignature.pParameters = rootParameters;
//descriptionRootSignature.NumParameters = _countof(rootParameters);

/*---------*/

struct PixelShaderOutput {

	float32_t4 color : SV_TARGET0;
};


PixelShaderOutput main() {
	PixelShaderOutput output;
	output.color = float32_t4(1.0, 1.0, 1.0, 1.0);

	return output;
}
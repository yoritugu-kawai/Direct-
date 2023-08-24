#pragma once
#include"DxCommon.h"
class PipelineState
{
public:
	void DXC();
	void CreatePSO();

private:
	HRESULT hr;//
	/*DIX*/
	IDxcUtils* dxcUtils;/*後々の可能性あり*/
	IDxcCompiler3* dxcCompiler;/*後々の可能性あり*/
	IDxcIncludeHandler* includeHandler;/*後々の可能性あり*/
};

#pragma once
#include"../Base/DxCommon.h"
#include"../Base/WinApp.h"
class ImguiManager
{
public:
	void Initialize();
	void BeginFrame();
	void EndFrame();
	void Release();
private:
	WinApp winApp_;
	DxCommon dxCommon_;
};

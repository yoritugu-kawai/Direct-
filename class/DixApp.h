#pragma once
#include<d3d12.h>
#include<dxgi1_6.h>
#include<cassert>
#include<string>
#include<Windows.h>
#include <cstdint>

#pragma comment(lib,"dxguid.lib")
#pragma comment(lib,"d3d12.lib")
class DixApp
{
public:
	void Initialize();
	void Log(const std::string& message);
private:
	HRESULT hr;
	D3D_FEATURE_LEVEL featureLevels[];

};

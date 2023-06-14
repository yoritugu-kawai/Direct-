#pragma once
#include<Windows.h>
#include <cstdint>
#include<string>
#include<format>
#include<d3d12.h>
#include<dxgi1_6.h>
#include<cassert>
#include<dxgidebug.h>
#include"WinApp.h"
#include"DixApp.h"
#include<dxcapi.h>

#pragma comment(lib,"dxguid.lib")
#pragma comment(lib,"d3d12.lib")
#pragma comment(lib,"dxgi.lib")
#pragma comment(lib,"dxcompiler.lib")
struct Vector4
{
	float x;
	float y;
	float z;
	float w;
};
class DixApp
{
public:
	/// <summary>
	/// DIXの初期設定
	/// </summary>
	void CreateFactory();
	void CreateAdapter();
	void CreateDevice();
	/// <summary>
	/// 青画面
	/// </summary>
	void CreateCommandQueue();
	void CreateCommandList();
	void CreateSwapChain(HWND hwnd);
	void CreateDescriptorHeap();
	void CreateSwChResce();
	void CreateRTV();
	//ループさせる
	void CommandLoad();
	void Commandkick();

	/// <summary>
	/// DIXの初期化
	/// </summary>
	void Initialize(HWND hwnd);
	void Update();
	void POS();
	void Release(HWND hwnd);

	
	


private:
	/// <summary>
	/// ファクトリーの作成
	/// </summary>
	IDXGIFactory7* dxgiFactory;
	HRESULT hr;
	/// <summary>
	/// アダプターの作成
	/// </summary>
	IDXGIAdapter4* useAdapter;
	/// <summary>
	/// Deviceの作成
	/// </summary>
	ID3D12Device* device;
	/// <summary>
	/// 
	/// </summary>
	ID3D12CommandQueue* commandQueue;

};

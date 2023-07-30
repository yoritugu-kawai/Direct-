#pragma once
#include<Windows.h>
#include <cstdint>
#include"Dxcommen.h"

#include"../externals/imgui/imgui.h"
#include"../externals/imgui/imgui_impl_dx12.h"
#include"../externals/imgui/imgui_impl_win32.h"
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
class WinApp
{
public:
	static LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
	WinApp(const wchar_t* title, const int32_t kClientWidth, const int32_t kClientHeight);
	void Initialize();
	void Release();
	int Width() { return kClientWidth_; }
	int Height() { return kClientHeight_; }
	HWND Gethwnd() { return hwnd_; }

private:
	WNDCLASS wc{};
	HWND hwnd_;
	const wchar_t* title_;
	int32_t kClientWidth_;
	int32_t kClientHeight_;
	ID3D12Debug1* deugController;
};



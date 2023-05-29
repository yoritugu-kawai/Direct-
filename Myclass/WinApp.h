#pragma once
#include<Windows.h>
#include <cstdint>
#include"DixApp.h"

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
	ID3D12Debug1* deugController = nullptr;
};



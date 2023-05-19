#pragma once
#include<Windows.h>
#include <cstdint>
#include"DixApp.h"

class WinApp
{
public:
	static LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
	void Initialize(const wchar_t* title, const int32_t kClientWidth, const int32_t kClientHeight);
	HWND hwnd;
private:
	WNDCLASS wc{};

};



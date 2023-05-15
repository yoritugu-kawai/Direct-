#pragma once
#include<Windows.h>
#include <cstdint>
#include<string>
class WindowsClass
{
public:
	static LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
	void Initialize(const int32_t kClientWidth, const int32_t kClientHeight);
private:
	WNDCLASS wc{};
	HWND hwnd;
};




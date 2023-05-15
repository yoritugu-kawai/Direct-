#pragma once
#include<Windows.h>
#include <cstdint>
class WindowsClass
{
public:
	
	void Initialize(const int32_t kClientWidth, const int32_t kClientHeight);
private:
	WNDCLASS wc{};
	HWND hwnd;
};




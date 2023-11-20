#include"TypManagement.h"

TypManagement* TypManagement::GetInstance()
{
	static TypManagement instance;
	return &instance;
}

void TypManagement::Initialize()
{
	Sprite::Initialize();
}



void TypManagement::Release()
{
	Sprite::Release();

}

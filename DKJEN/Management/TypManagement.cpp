#include"TypManagement.h"

TypManagement* TypManagement::GetInstance()
{
	static TypManagement instance;
	return &instance;
}

void TypManagement::Initialize(ImageLoading* imageLoading)
{
	TexProeerty tex = imageLoading->LoadTexture("resource/e.png");
	Transfrom SpriteTrans =
	{
		{560.f,0.0f,0.0f,1.0f},
		{ 0.0f,360.0f,0.0f,1.0f },
		{560.0f,360.0f,0.0f,1.0f}

	};
	Sprite::Initialize(tex, SpriteTrans.lefe, SpriteTrans.top, SpriteTrans.right);
}



void TypManagement::Release()
{
	Sprite::Release();

}

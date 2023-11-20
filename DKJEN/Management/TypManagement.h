#pragma once
#include"../Type/Sprite.h"
#include"DKJEN/Type/Polygon.h"

#include"DKJEN/Type/Texture.h"
#include"DKJEN/Type/Sphere.h"
#include"DKJEN/Type/Obj3D.h"
struct Transfrom
{
	Vector4 lefe;
	Vector4  top;
	Vector4 right;
	Vector4 color;

};
class TypManagement
{
public:
	static TypManagement* GetInstance();
	static void Initialize(ImageLoading* imageLoading);

	static void Release();
private:

};

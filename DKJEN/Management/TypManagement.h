#pragma once
#include"../Type/Sprite.h"
#include"DKJEN/Type/Polygon.h"

#include"DKJEN/Type/Texture.h"
#include"DKJEN/Type/Sphere.h"
#include"DKJEN/Type/Obj3D.h"
class TypManagement
{
public:
	static TypManagement* GetInstance();
	static void Initialize();

	static void Release();
private:

};

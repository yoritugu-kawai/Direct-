#pragma once
#include<Windows.h>
#include <cstdint>
#include<string>
#include<format>
#include<d3d12.h>
#include<dxgi1_6.h>
#include<cassert>
#include<dxgidebug.h>
#include<dxcapi.h>

#pragma comment(lib,"dxguid.lib")
#pragma comment(lib,"d3d12.lib")
#pragma comment(lib,"dxgi.lib")
#pragma comment(lib,"dxcompiler.lib")
struct  Vector3
{
	float x;
	float y;
	float z;

};
struct Vector4
{
	float x;
	float y;
	float z;
	float w;
};
struct   Matrix4x4 {
	float m[4][4];
};
Matrix4x4 MakeIdentity4x4();

struct  Transfom
{
	Vector3 scale;
	Vector3 rotate;
	Vector3 translate;
};
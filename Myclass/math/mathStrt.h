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
/// <summary>
/// 数学
/// </summary>
/// <returns></returns>
Matrix4x4 MakeIdentity4x4();
Matrix4x4 MakeScaleMatrix(const Vector3 scale);
Matrix4x4 MakeRotateXMatrix(float radian);
Matrix4x4 MakeRotateYMatrix(float radian);
Matrix4x4 MakeRotateZMatrix(float radian);
Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2);
Matrix4x4 MakeRotateXYZMatrix(float radianX, float radianY, float radianZ);
Matrix4x4 MakeTranslateMatrix(const Vector3 translate);
Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rotate, const Vector3& translate);

struct  Transfom
{
	Vector3 scale;
	Vector3 rotate;
	Vector3 translate;
};
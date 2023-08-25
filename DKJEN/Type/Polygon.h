#pragma once
#include"../Math/Math.h"
class Polygon
{
public:
	void Initialize( Vector4 pos, Vector4 Color);
	void Draw();
	void Release();
private:
	Vector4 CenterPos_ = { 0.0f,0.0f,0.0f };
	Vector4 Color_ = { 0.0f,0.0f,1.0f,1.0f };
	const float size = 0.1f;
};

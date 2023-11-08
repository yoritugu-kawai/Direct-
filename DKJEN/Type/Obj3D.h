#pragma once
#include"../Base/ObjLoad.h"
#include"../Math/Math.h"
#include"../Base/DxCommon.h"
#include"../Base/LightPSO.h"
class Obj3D {
public:
	void Initialize(TexProeerty  tex);
	void Draw(Matrix4x4 m);
	ID3D12Resource* CreateBufferResource(size_t sizeInbyte);
private:
	ID3D12Resource* vetexResource;
	ID3D12Resource* materialResource;
	ID3D12Resource* wvpResource;
	ID3D12Resource* lightResource;

	D3D12_VERTEX_BUFFER_VIEW vertxBufferView{};
	ModelData modelData;

	TexProeerty  tex_;
};

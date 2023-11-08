#pragma once
#include"../Math/Math.h"
#include"ImageLoading.h"
#include<fstream>
#include<sstream>
struct ModelData
{
	std::vector<VertexData>vertices;

};

ModelData LoadObjFile(const std::string& directiry,const std::string& filename);
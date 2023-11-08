#pragma once
#include"../Math/Math.h"
#include"ImageLoading.h"
#include<fstream>
#include<sstream>
struct MaterialData {
	std::string textureFilePath;
};

struct ModelData
{
	std::vector<VertexData>vertices;
	MaterialData material;
};




ModelData LoadObjFile(const std::string& directiry,const std::string& filename, TexProeerty tex_);

MaterialData LoadMaterialTemplateFile(const std::string& directiry, const std::string& filename);
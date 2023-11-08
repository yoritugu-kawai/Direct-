#include"ObjLoad.h"

ModelData LoadObjFile(const std::string& directoryPath, const std::string& filename, TexProeerty tex)
{
	//1.
	ModelData modelData;
	std::vector<Vector4>positions;
	std::vector<Vector3>normals;
	std::vector<Vector2>texcoords;
	std::string line;
	
	//2.
	std::ifstream file(directoryPath + "/" + filename);
	assert(file.is_open());
	
	//3.
	while (std::getline(file, line)) {
		std::string identifier;
		std::istringstream s(line);
		s >> identifier;
		//identifier処理
		if (identifier == "v") {
			Vector4 position;
			s >> position.x >> position.y >> position.z;
			position.z *= -1.0f;
			position.w = 1.0f;
			positions.push_back(position);
		}
		else if (identifier == "vt") {
			Vector2 texcoord;
			s >> texcoord.x >> texcoord.y;
			texcoord.y *= -1.0f;
			texcoords.push_back(texcoord);
		}
		else if (identifier == "vn") {
			Vector3 normal;
			s >> normal.x >> normal.y >> normal.z;
			normal.z *= -1.0f;
			normals.push_back(normal);
		}
		else if (identifier == "f") {
			VertexData triangle[3];
			for (int32_t faceVertex = 0; faceVertex < 3; ++faceVertex) {
				std::string vertexDefinition;
				s >> vertexDefinition;
				std::istringstream v(vertexDefinition);
				uint32_t elementIndices[3];
				for (int32_t element = 0; element < 3; ++element) {
					std::string index;
					std::getline(v, index, '/');
					elementIndices[element] = std::stoi(index);
				}
				Vector4 position = positions[elementIndices[0] - 1];
				Vector2 texcoord = texcoords[elementIndices[1] - 1];
				Vector3 normal = normals[elementIndices[2] - 1];
				/*VertexData vertex = { position,texcoord,normal };
				modelData.vertices.push_back(vertex);*/
				triangle[faceVertex] = { position,texcoord,normal };
			}
			modelData.vertices.push_back(triangle[2]);
			modelData.vertices.push_back(triangle[1]);
			modelData.vertices.push_back(triangle[0]);
		}
		else if (identifier == "mtllib") {
			//tex
			std::string materialFilename;
			s >> materialFilename;
			modelData.material= LoadMaterialTemplateFile(directoryPath, materialFilename);
		}
	}
	/*ImageLoading* imgload = new ImageLoading;
	tex= imgload->LoadTexture(modelData.material.textureFilePath);
	*/
	//4.
	
	return modelData;
}

MaterialData LoadMaterialTemplateFile(const std::string& directiry, const std::string& filename)
{
	MaterialData materialData;
	std::string line;
	std::ifstream file(directiry + "/" + filename);
	assert(file.is_open());
	while (std::getline(file, line)) {
		std::string identifier;
		std::istringstream s(line);
		s >> identifier;
		if (identifier == "map_Kd") {
			std::string textureFilename;
			s >> textureFilename;
			materialData.textureFilePath = directiry + "/" + textureFilename;
		}
	}
	return materialData;
}

#ifndef _MODEL_H_
#define _MODEL_H_

#include <vector>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "Mesh.h"

class Model
{
public:
	Model(const char* path);
	void draw(const Shader& shader);
private:
	void loadModel(const std::string& path);
	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, const std::string& typeName);
	GLint TextureFromFile(const char* path, const std::string& directory);
private:
	std::vector<Mesh> _meshes;
	std::string _directory;
	std::vector<Texture> _loadedTextures;
};

#endif//_MODEL_H_

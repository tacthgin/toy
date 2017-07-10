#include "Model.h"
#include <iostream>
#include <SOIL/SOIL.h>

using namespace std;
using namespace Assimp;

Model::Model(const char * path)
{
	if(path != nullptr)
		loadModel(path);
}

void Model::draw(const Shader & shader)
{
	for (auto& mesh : _meshes)
		mesh.draw(shader);
}

void Model::loadModel(const std::string & path)
{
	Importer import;
	const aiScene* scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
	if (scene == nullptr || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || scene->mRootNode == nullptr)
	{
		cout << "ERROR::ASSIMP::" << import.GetErrorString() << endl;
		return;
	}
	_directory = path.substr(0, path.find_last_of("/"));
	processNode(scene->mRootNode, scene);
}

void Model::processNode(aiNode * node, const aiScene * scene)
{
	for (GLuint i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		_meshes.push_back(processMesh(mesh, scene));
	}

	for (GLuint i = 0; i < node->mNumChildren; i++)
	{
		processNode(node->mChildren[i], scene);
	}
}

Mesh Model::processMesh(aiMesh * mesh, const aiScene * scene)
{
	vector<Vertex> vertices;
	vector<GLuint> indices;
	vector<Texture> textures;

	for (GLuint i = 0; i < mesh->mNumVertices; i++)
	{
		Vertex vertex;
		aiVector3D aiVertex = mesh->mVertices[i];
		vertex.position = glm::vec3(aiVertex.x, aiVertex.y, aiVertex.z);

		aiVector3D aiNormal = mesh->mNormals[i];
		vertex.normal = glm::vec3(aiNormal.x, aiNormal.y, aiNormal.z);

		aiVector3D* texCoords0 = mesh->mTextureCoords[0];
		if (texCoords0 != nullptr)
		{
			vertex.texCoords = glm::vec2(texCoords0[i].x, texCoords0[i].y);
		}
		else
		{
			vertex.texCoords = glm::vec2(0.0f, 0.0f);
		}

		vertices.push_back(vertex);
	}

	for (GLuint i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace* face = &mesh->mFaces[i];
		for (GLuint j = 0; j < face->mNumIndices; j++)
		{
			indices.push_back(face->mIndices[j]);
		}
	}

	if (mesh->mMaterialIndex >= 0)
	{
		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
		vector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
		textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
		vector<Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
		textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
	}

	return Mesh(vertices, indices, textures);
}

std::vector<Texture> Model::loadMaterialTextures(aiMaterial * mat, aiTextureType type, const std::string & typeName)
{
	vector<Texture> textures;
	for (GLuint i = 0; i < mat->GetTextureCount(type); i++)
	{
		aiString str;
		mat->GetTexture(type, i, &str);
		GLboolean skip = false;
		for (auto& loadTexture : _loadedTextures)
		{
			if (loadTexture.path == str.C_Str())
			{
				textures.push_back(loadTexture);
				skip = true;
				break;
			}
		}
		if (!skip)
		{
			Texture texture;
			texture.id = TextureFromFile(str.C_Str(), _directory);
			texture.type = typeName;
			texture.path = str.C_Str();
			textures.push_back(texture);
			_loadedTextures.push_back(texture);
		}
	}
	return textures;
}

GLint Model::TextureFromFile(const char * path, const std::string & directory)
{
	string filename = directory + "/" + path;
	GLuint textureId;
	glGenTextures(1, &textureId);
	int width, height;
	unsigned char* image = SOIL_load_image(filename.c_str(), &width, &height, 0, SOIL_LOAD_RGBA);

	glBindTexture(GL_TEXTURE_2D, textureId);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);
	SOIL_free_image_data(image);

	return textureId;
}

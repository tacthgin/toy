#ifndef _MESH_H_
#define _MESH_H_

#include <vector>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shader.h"

class Vertex
{
public:
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texCoords;
};

class Texture
{
public:
	GLuint id;
	std::string type;
	std::string path;
};

class Mesh
{
public:
	Mesh(const std::vector<Vertex>& vertices, const std::vector<GLuint>& indices, const std::vector<Texture>& textures);
	~Mesh();
	void draw(const Shader& shader);
private:
	void setupMesh();
private:
	GLuint _VAO;
	GLuint _VBO;
	GLuint _EBO;
	std::vector<Vertex> _vertices;
	std::vector<GLuint> _indices;
	std::vector<Texture> _textures;
};

#endif //_MESH_H_
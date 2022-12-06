#pragma once
#ifndef Mesh_h
#define Mesh_h

#include <GL/glew.h>
#include <vector>
#include "Math/float2.h"
#include <assimp/mesh.h>

class Mesh
{
public:
	Mesh(unsigned int material_index)
	{
		this->material_index=material_index;
	}
	void LoadVBO(const aiMesh* mesh);
	void LoadVBOInterleaved(const aiMesh* mesh);
	void LoadEBO(const aiMesh* mesh);
	void CreateVAO();
	void CreateVAOInterleaved();
	void Draw(const std::vector< std::vector< unsigned > >& material, unsigned int programId);
	
private:
	GLuint vao;
	GLuint vbo;
	GLuint ebo;
	int mVertices;
	int num_vertices;
	int num_indices;
	unsigned int material_index;
	float2* uvs;
};
#endif
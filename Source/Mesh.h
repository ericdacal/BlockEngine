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
	Mesh(unsigned int materialIndex);
	void LoadVBO(const aiMesh* mesh);
	void LoadVBOInterleaved(const aiMesh* mesh);
	void LoadEBO(const aiMesh* mesh);
	void CreateVAO();
	void CreateVAOInterleaved();
	void Draw(const std::vector< std::vector< unsigned > >& material, unsigned int programId);
	int getNumVertices();
	int getNumTriangles();
	
private:
	GLuint vao;
	GLuint vbo;
	GLuint ebo;
	int numVertices;
	int numIndices;
	int numTriangles;
	unsigned int materialIndex;
	float2* uvs;
};
#endif
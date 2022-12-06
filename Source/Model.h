#pragma once
#ifndef Model_h
#define Model_h

#include <vector>
#include <GL/glew.h>
#include "DirectXTex.h"


struct Mesh;
struct aiScene;

class Model
{
	public:
		void Load(const char* file_name);
		void Draw();
		void Clean();
	private:
		bool findPath(const char* path, char* file);
		void LoadMaterials(const aiScene* scene);
		void LoadMeshes(const aiScene* scene);
		char* LoadShaderSource(const char* shader_file_name);
		void LoadTextureGPU(const DirectX::ScratchImage* im, int index);
		unsigned CompileShader(unsigned type, const char* source);
		std::vector< std::vector<unsigned int>> materials;
		std::vector< unsigned int > material_index;
		std::vector<Mesh*> meshes;
		std::vector<GLuint> shadersIds;
		int num_vertices;
		int num_indices;
		GLuint programId;
};

#endif
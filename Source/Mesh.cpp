#include "Application.h"
#include "Modules/ModuleCameraEditor.h"
#include "Mesh.h"


Mesh::Mesh(unsigned int materialIndex)
{
	this->materialIndex = materialIndex;
	numIndices = 0;
	numTriangles = 0;
	numVertices = 0;
}

int Mesh::getNumVertices() {
	return numVertices;
}
int Mesh::getNumTriangles() {
	return numTriangles;
}

void Mesh::CreateVAO()
{
	//FOR SEPARATED ARRAY ATRIBUTES
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)(sizeof(float) * 3 * numVertices));
}

void Mesh::CreateVAOInterleaved() 
{
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3 + sizeof(float) * 2, (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 3 + sizeof(float) * 2, (void*)(sizeof(float) * 3));
}


void Mesh::LoadVBO(const aiMesh* mesh) {
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	unsigned vertex_size = (sizeof(float) * 3 + sizeof(float) * 2);
	unsigned buffer_size = vertex_size * mesh->mNumVertices;
	glBufferData(GL_ARRAY_BUFFER, buffer_size, nullptr, GL_STATIC_DRAW);
	unsigned position_size = sizeof(float) * 3 * mesh->mNumVertices;
	glBufferSubData(GL_ARRAY_BUFFER, 0, position_size, mesh->mVertices);
	unsigned uv_offset = position_size;
	unsigned uv_size = sizeof(float) * 2 * mesh->mNumVertices;
	float2* uvs = (float2*)(glMapBufferRange(GL_ARRAY_BUFFER, uv_offset, uv_size, GL_MAP_WRITE_BIT));
	for (unsigned i = 0; i < mesh->mNumVertices; ++i)
	{
		uvs[i] = float2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y);
	}
	glUnmapBuffer(GL_ARRAY_BUFFER);
	numVertices = mesh->mNumVertices;
}


void Mesh::LoadVBOInterleaved(const aiMesh* mesh)
{
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, (sizeof(float) * 3 + sizeof(float) * 2) * mesh->mNumVertices, nullptr, GL_STATIC_DRAW);
	float* buffer = (float*)(glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY));
	for (unsigned i = 0; i < mesh->mNumVertices; ++i)
	{
		*(buffer++) = mesh->mVertices[i].x;
		*(buffer++) = mesh->mVertices[i].y;
		*(buffer++) = mesh->mVertices[i].z;

		*(buffer++) = mesh->mTextureCoords[0][i].x;
		*(buffer++) = mesh->mTextureCoords[0][i].y;
	}
	glUnmapBuffer(GL_ARRAY_BUFFER);
	APPLOG("Mesh Vertices: %d", mesh->mNumVertices);
	numVertices = mesh->mNumVertices;
}



void Mesh::LoadEBO(const aiMesh* mesh)
{
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	unsigned index_size = sizeof(unsigned) * mesh->mNumFaces * 3;
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_size, nullptr, GL_STATIC_DRAW);
	unsigned* indices = (unsigned*)(glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_WRITE_ONLY));
	//unsigned* indices = (unsigned*)(glMapBufferRange(GL_ELEMENT_ARRAY_BUFFER, 0, index_size, GL_MAP_WRITE_BIT));
	
	for (unsigned i = 0; i < mesh->mNumFaces; ++i)
	{
		APPLOG("Num Indices: %d", mesh->mFaces[i].mNumIndices);
	
		assert(mesh->mFaces[i].mNumIndices == 3); // note: assume triangles = 3 indices per face
		if (mesh->mFaces[i].mNumIndices == 3) {
			*(indices++) = mesh->mFaces[i].mIndices[0];
			*(indices++) = mesh->mFaces[i].mIndices[1];
			*(indices++) = mesh->mFaces[i].mIndices[2];
		}
	}
	glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);
	APPLOG("Mesh Faces: %d", mesh->mNumFaces);
	numTriangles = mesh->mNumFaces;
	numIndices = mesh->mNumFaces * 3;
}

void Mesh::Draw(const std::vector< std::vector< unsigned > >& materials, unsigned int programId)
{
	const float4x4& view = App->camEditor->GetViewMatrix();
	const float4x4& proj = App->camEditor->GetProjectionMatrix();
	float4x4 model = float4x4::identity;
	glUseProgram(programId);
	glUniformMatrix4fv(glGetUniformLocation(programId, "model"), 1, GL_TRUE, (const float*)&model);
	glUniformMatrix4fv(glGetUniformLocation(programId, "view"), 1, GL_TRUE, (const float*)&view);
	glUniformMatrix4fv(glGetUniformLocation(programId, "proj"), 1, GL_TRUE, (const float*)&proj);
	glUniform1i(glGetUniformLocation(programId, "diffuse"), 0);
	glBindVertexArray(vao);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, materials[materialIndex][0]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_INT, nullptr);
	glBindVertexArray(0);
}
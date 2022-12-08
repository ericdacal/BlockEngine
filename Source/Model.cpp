#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "Application.h"
#include "Mesh.h"
#include "Modules/ModuleTexture.h"
#include "Modules/ModuleProgram.h"
#include "Model.h"
#include <filesystem>

namespace fs = std::filesystem;


char* Model::LoadShaderSource(const char* shader_file_name)
{
	char* data = nullptr;
	FILE* file = nullptr;
	fopen_s(&file, shader_file_name, "rb");
	if (file)
	{
		fseek(file, 0, SEEK_END);
		int size = ftell(file);
		data = (char*)malloc(size + 1);
		fseek(file, 0, SEEK_SET);
		fread(data, 1, size, file);
		data[size] = 0;
		fclose(file);
	}
	return data;
}


unsigned Model::CompileShader(unsigned type, const char* source)
{
	unsigned shader_id = glCreateShader(type);
	glShaderSource(shader_id, 1, &source, 0);
	glCompileShader(shader_id);
	int res = GL_FALSE;
	glGetShaderiv(shader_id, GL_COMPILE_STATUS, &res);
	if (res == GL_FALSE)
	{
		int len = 0;
		glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &len);
		if (len > 0)
		{
			int written = 0;
			char* info = (char*)malloc(len);
			glGetShaderInfoLog(shader_id, len, &written, info);
			APPLOG("Log Info: %s", info);
			//App->logs.push_back("Destroying shaders");
			free(info);
		}
	}
	return shader_id;
}

void Model::Clean() 
{
	materials.clear();
	materialIndex.clear();
	meshes.clear();
}

void Model::Load(const char* file_name)
{
	numVertices = 0;
	numTriangles = 0;
	Clean();
	APPLOG("Loading Shader files");
	//App->logs.push_back({ "Loading Shader files", ImVec4(1.f,0.f,0.f,1.f) });
	GLchar* vshader = LoadShaderSource("../Source/Shaders/vert.glsl");
	GLchar* fshader = LoadShaderSource("../Source/Shaders/frag.glsl");

	APPLOG("Compiling Shader files");
	//App->logs.push_back({ "Compiling Shader files", ImVec4(1.f,0.f,0.f,1.f) });
	GLuint vCompile = CompileShader(GL_VERTEX_SHADER, vshader);
	GLuint fCompile = CompileShader(GL_FRAGMENT_SHADER, fshader);
	shadersIds.push_back(vCompile);
	shadersIds.push_back(fCompile);

	APPLOG("Creating Program");
	//App->logs.push_back({ "Creating Program", ImVec4(1.f,0.f,0.f,1.f) });
	programId = App->program->CreateProgram(vCompile, fCompile);


	const aiScene* scene = aiImportFile(file_name, aiProcess_Triangulate);
	if (scene)
	{
		LoadMaterials(scene);
		LoadMeshes(scene);
		
	}
	else
	{
		APPLOG("Error loading %s: %s", file_name, aiGetErrorString());
	}
}

void Model::LoadMaterials(const aiScene* scene)
{
	aiString file;
	APPLOG("Num. Materials: %d", scene->mNumMaterials);
	materials.reserve(scene->mNumMaterials);
	for (unsigned i = 0; i < scene->mNumMaterials; ++i)
	{
		materials.push_back(std::vector<unsigned int>());
		bool find = true;
		if (scene->mMaterials[i]->GetTexture(aiTextureType_DIFFUSE, 0, &file) == AI_SUCCESS)
		{
			if (not findPath(".\\%s", file.data)) {
				APPLOG("Not exist .\\%s", file.data);
				if (not findPath("..\\Game\\assets\\resources\\%s", file.data)) {
					APPLOG("Not exist ..\\Game\\assets\\resources\\%s", file.data);
					if (not findPath("..\\Game\\assets\\resources\\Textures\\%s", file.data)) {
						APPLOG("Not exist ..\\Game\\assets\\resources\\Textures\\%s", file.data);
						assert("Texture not find");
						diffusePath = aiString("../Game/assets/resources/Textures/no_texture.png");
						const DirectX::ScratchImage* im = App->texture->Load(diffusePath.data);
						LoadTextureGPU(im, i);
						find = false;
					}
					else diffusePath = aiString("../Game/assets/resources/Textures/");
				}
				else diffusePath = aiString("../Game/assets/resources/");;
			}
			else diffusePath = aiString("./");
			if (find) {
				diffusePath.Append(file.data);
				const DirectX::ScratchImage* im = App->texture->Load(diffusePath.data);
				LoadTextureGPU(im, i);
			}		
		}
		else {
			diffusePath = aiString("../Game/assets/resources/Textures/no_texture.png");
			const DirectX::ScratchImage* im = App->texture->Load(diffusePath.data);
			LoadTextureGPU(im, i);
		}
	}
}

void Model::LoadMeshes(const aiScene* scene)
{
	meshes.reserve(scene->mNumMeshes);
	APPLOG("Num Meshes: %d", scene->mNumMeshes);
	
	for (unsigned i = 0; i < scene->mNumMeshes; ++i) 
	{
		Mesh* mesh = new Mesh(scene->mMeshes[i]->mMaterialIndex);
		mesh->LoadVBOInterleaved(scene->mMeshes[i]);
		mesh->LoadEBO(scene->mMeshes[i]);
		mesh->CreateVAOInterleaved();
		meshes.push_back(mesh);
		numVertices += mesh->getNumVertices();
		numTriangles += mesh->getNumTriangles();
	}
}

void Model::Draw() 
{
	for (int i = 0; i < meshes.size(); ++i) {
		(*(meshes[i])).Draw(materials, programId);
	}
}

bool Model::findPath(const char* path, char* file) {
	char tempFile[200];
	sprintf_s(tempFile, 200, path, file);
	if (not fs::exists(tempFile)) {
		return false;
	}
	return true;
}

void Model::LoadTextureGPU(const DirectX::ScratchImage* im, int index) {
	APPLOG("Create Textures");
	GLuint textureId;
	glGenTextures(1, &textureId);
	materials[index].push_back(textureId);


	glBindTexture(GL_TEXTURE_2D, textureId);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);



	GLint internalFormat;
	GLint format;
	GLint type;
	APPLOG("%d", im->GetMetadata().format);
	switch (im->GetMetadata().format)
	{
		case DXGI_FORMAT_R8G8B8A8_UNORM_SRGB:
			internalFormat = GL_RGBA8;
			format = GL_RGBA;
			type = GL_UNSIGNED_BYTE;
			break;
		case DXGI_FORMAT_R8G8B8A8_UNORM:
			internalFormat = GL_RGBA8;
			format = GL_RGBA;
			type = GL_UNSIGNED_BYTE;
			break;
		case DXGI_FORMAT_B8G8R8A8_UNORM_SRGB:
			internalFormat = GL_RGBA8;
			format = GL_BGRA;
			type = GL_UNSIGNED_BYTE;
			break;
		case DXGI_FORMAT_B8G8R8A8_UNORM:
			internalFormat = GL_RGBA8;
			format = GL_BGRA;
			type = GL_UNSIGNED_BYTE;
			break;
		case DXGI_FORMAT_B5G6R5_UNORM:
			internalFormat = GL_RGB8;
			format = GL_BGR;
			type = GL_UNSIGNED_BYTE;
			break;
		default:
			APPLOG("Unsopported format");
			assert(false && "Unsupported format");
	}
	glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, im->GetMetadata().width, im->GetMetadata().height, 0, format, type, im->GetPixels());
	glGenerateMipmap(GL_TEXTURE_2D);
	glActiveTexture(GL_ACTIVE_TEXTURE);
}

const char* Model::getDiffuseTexture() {
	return diffusePath.data;
}
int Model::getNumVertices() {
	return numVertices;
}
int Model::getNumTriangles() {
	return numTriangles;
}



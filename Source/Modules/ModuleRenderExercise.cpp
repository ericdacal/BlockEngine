#include "../Globals.h"
#include "../Application.h"
#include "ModuleRenderExercise.h"
#include "ModuleWindow.h"
#include "ModuleProgram.h"
#include "ModuleCameraEditor.h"
#include <SDL.h>
#include <Geometry/Frustum.h>
#include <Math/MathConstants.h>
#include <Math/float3.h>

ModuleRenderExercise::ModuleRenderExercise()
{
}

// Destructor
ModuleRenderExercise::~ModuleRenderExercise()
{
}

bool ModuleRenderExercise::Init()
{

	bool ret = true;

	APPLOG("Create VBOs");
	App->NewLog("Create VBOs", 0);
	VBOIds.push_back(CreateTriangleVBO());

	APPLOG("Loading Shader files");
	App->NewLog("Loading Shader files", 0);
	GLchar* vshader = LoadShaderSource("..\\Source\\Shaders\\vert.glsl");
	GLchar* fshader = LoadShaderSource("..\\Source\\Shaders\\frag.glsl");

	APPLOG("Compiling Shader files");
	App->NewLog("Compiling Shader files", 0);
	GLuint vCompile = CompileShader(GL_VERTEX_SHADER, vshader);
	GLuint fCompile = CompileShader(GL_FRAGMENT_SHADER, fshader);
	shadersIds.push_back(vCompile);
	shadersIds.push_back(fCompile);

	APPLOG("Creating Program");
	App->NewLog("Creating Program", 0);
	programId = App->program->CreateProgram(vCompile, fCompile);

	return ret;
}

update_status ModuleRenderExercise::Update()
{
	update_status ret = UPDATE_CONTINUE;
	GLsizei w = NULL;
	GLsizei h = NULL;
	SDL_GetWindowSize(App->window->window, &w, &h);
	glViewport(0, 0, w, h);
	glClearColor(0.f, 0.f, 0.f, 0.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	for (std::list<GLuint>::iterator it = VBOIds.begin(); it != VBOIds.end(); ++it)
	{
		RenderVBO((*it), programId);
	}
	return ret;
}

bool ModuleRenderExercise::CleanUp() {
	APPLOG("Destroying VBOs");
	App->NewLog("Destroying VBOs", 0);
	for (std::list<GLuint>::iterator it = VBOIds.begin(); it != VBOIds.end(); ++it)
	{
		DestroyVBO((*it));
	}
	// Destroy shaders
	APPLOG("Destroying shaders");
	App->NewLog("Destroying shaders", 0);
	for (std::list<GLuint>::iterator it = shadersIds.begin(); it != shadersIds.end(); ++it)
	{
		glDeleteShader(*it);
	}
	return true;
}


GLuint ModuleRenderExercise::CreateTriangleVBO()
{
	float vtx_data[] = { -1.0f, -1.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f };
	unsigned vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo); // set vbo active
	glBufferData(GL_ARRAY_BUFFER, sizeof(vtx_data), vtx_data, GL_STATIC_DRAW);
	return vbo;
}


char* ModuleRenderExercise::LoadShaderSource(const char* shader_file_name)
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

void LoadTextureGPU(const DirectX::ScratchImage* im) {
	GLuint textureId;
	glGenTextures(1, &textureId);

	glBindTexture(GL_TEXTURE_2D, textureId);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
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
		assert(false && "Unsupported format");
	}
	glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, im->GetMetadata().width, im->GetMetadata().height, 0, format, type, im->GetPixels());
	glGenerateMipmap(GL_TEXTURE_2D);
	glActiveTexture(GL_ACTIVE_TEXTURE);
}


unsigned ModuleRenderExercise::CompileShader(unsigned type, const char* source)
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
			free(info);
		}
	}
	return shader_id;
}
// This function must be called each frame for drawing the triangle
void ModuleRenderExercise::RenderVBO(unsigned vbo, unsigned program)
{
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glEnableVertexAttribArray(0);
	// size = 3 float per vertex
	// stride = 0 is equivalent to stride = sizeof(float)*3
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glUseProgram(program);

	
	float4x4 model = float4x4::FromTRS(float3(2.0f, 0.0f, 0.0f), float4x4::RotateZ(pi / 4.0f), float3(2.0f, 1.0f, 0.0f));


	glUniformMatrix4fv(glGetUniformLocation(program, "model"), 1, GL_TRUE, &model[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(program, "view"), 1, GL_TRUE, &App->camEditor->GetViewMatrix()[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(program, "proj"), 1, GL_TRUE, &App->camEditor->GetProjectionMatrix()[0][0]);
	// 1 triangle to draw = 3 vertices
	glDrawArrays(GL_TRIANGLES, 0, 3);
}



// This function must be called one time at destruction of vertex buffer
void ModuleRenderExercise::DestroyVBO(unsigned vbo)
{
	glDeleteBuffers(1, &vbo);
}
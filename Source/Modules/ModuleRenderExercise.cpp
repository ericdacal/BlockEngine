#include "../Globals.h"
#include "../Application.h"
#include "ModuleRenderExercise.h"
#include "ModuleWindow.h"
#include "ModuleProgram.h"
#include <SDL.h>

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

	LOG("Create VBOs");
	VBOIds.push_back(CreateTriangleVBO());

	LOG("Loading Shader files");
	GLchar* vshader = LoadShaderSource("..\\Source\\Shaders\\vert.glsl");
	GLchar* fshader = LoadShaderSource("..\\Source\\Shaders\\frag.glsl");

	LOG("Compiling Shader files");
	GLuint vCompile = CompileShader(GL_VERTEX_SHADER, vshader);
	GLuint fCompile = CompileShader(GL_FRAGMENT_SHADER, fshader);
	shadersIds.push_back(vCompile);
	shadersIds.push_back(fCompile);

	LOG("Creating Program");
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
	LOG("Destroying VBOs");
	for (std::list<GLuint>::iterator it = VBOIds.begin(); it != VBOIds.end(); ++it)
	{
		DestroyVBO((*it));
	}
	// Destroy shaders
	LOG("Destroying shaders");
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
	// 1 triangle to draw = 3 vertices
	glDrawArrays(GL_TRIANGLES, 0, 3);
}



// This function must be called one time at destruction of vertex buffer
void ModuleRenderExercise::DestroyVBO(unsigned vbo)
{
	glDeleteBuffers(1, &vbo);
}
#pragma once
#include "Module.h"
#include "../Globals.h"
#include<list>
#include <GL/glew.h>

struct SDL_Texture;
struct SDL_Renderer;
struct SDL_Rect;

class ModuleRenderExercise : public Module
{
public:
	ModuleRenderExercise();
	~ModuleRenderExercise();
	
	bool Init();
	update_status Update();
	bool CleanUp();

private:
	GLuint programId;
	std::list<GLuint> shadersIds;
	std::list<GLuint> VBOIds;
	void  RenderVBO(unsigned vbo, unsigned program);
	GLuint CreateTriangleVBO();
	void DestroyVBO(unsigned vbo);
	char* LoadShaderSource(const char* shader_file_name);
	unsigned CompileShader(unsigned type, const char* source);
};

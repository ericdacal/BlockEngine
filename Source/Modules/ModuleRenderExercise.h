#pragma once
#ifndef Module_Render_Exercise_h
#define Module_Render_Exercise_h

#include "Module.h"
#include "../Globals.h"
#include<list>
#include <GL/glew.h>
#include <Math/float4x4.h>

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
	float4x4 LookAt(float3 eye, float3 at, float3 up);
	GLuint programId;
	std::list<GLuint> shadersIds;
	std::list<GLuint> VBOIds;
	void  RenderVBO(unsigned vbo, unsigned program);
	GLuint CreateTriangleVBO();
	void DestroyVBO(unsigned vbo);
	char* LoadShaderSource(const char* shader_file_name);
	unsigned CompileShader(unsigned type, const char* source);
};
#endif
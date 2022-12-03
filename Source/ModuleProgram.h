#pragma once
#include "Module.h"
#include "Globals.h"


struct SDL_Texture;
struct SDL_Renderer;
struct SDL_Rect;

class ModuleProgram : public Module
{
public:
	ModuleProgram();
	~ModuleProgram();

	unsigned CreateProgram(unsigned vtx_shader, unsigned frg_shader);
};

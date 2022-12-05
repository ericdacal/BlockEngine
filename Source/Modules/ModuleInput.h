#pragma once
#ifndef Module_Input_h
#define Module_Input_h

#include "Module.h"
#include "../Globals.h"

typedef unsigned __int8 Uint8;

class ModuleInput : public Module
{
public:
	
	ModuleInput();
	~ModuleInput();

	bool Init();
	update_status Update();
	bool CleanUp();

private:
	const Uint8 *keyboard = NULL;
};
#endif
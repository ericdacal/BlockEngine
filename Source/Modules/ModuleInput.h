#pragma once
#ifndef Module_Input_h
#define Module_Input_h

#include "Module.h"
#include "../Globals.h"

typedef unsigned __int8 Uint8;
typedef unsigned __int64 Uint64;

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
	float cameraSpeed = 0.05f;
	float deltaTime = 0.0f;	// Time between current frame and last frame
	Uint64 lastFrame = 0; // Time of last frame
	bool leftMouseButton;
	bool rightMouseButton;
	bool leftAltButton;
};
#endif
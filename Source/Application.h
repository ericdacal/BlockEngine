#pragma once
#ifndef Application_h
#define Application_h

#include <list>
#include <vector>
#include <ctime>
#include "Globals.h"
#include "Modules/Module.h"

class ModuleRender;
class ModuleWindow;
class ModuleTextures;
class ModuleInput;
class ModuleGui;
class ModuleProgram;
class ModuleDebugDraw;
class ModuleCameraEditor;
class ModuleTexture;
class ModuleDrawer;


class Application
{
public:

	Application();
	~Application();

	bool Init();
	update_status Update();
	bool CleanUp();
	void NewLog(const char*, int priority);
	void RequestBrowser(const char* url);
	std::vector<AppLog> GetLogs();
	void setMaxFrameRate(float maxFps);

public:
	ModuleRender* renderer = nullptr;
	ModuleWindow* window = nullptr;
	ModuleInput* input = nullptr;
	ModuleProgram* program = nullptr;
	ModuleDebugDraw* debugDraw = nullptr;
	ModuleGui* gui = nullptr;
	ModuleCameraEditor* camEditor = nullptr;
	ModuleTexture* texture = nullptr;
	ModuleDrawer* drawer = nullptr;
	std::vector<float> fps;
	std::vector<float> milliseconds;
	

private:
	// Vector that allocates modules
	std::list<Module*> modules;
	
	// Vector that allocate logs 
	std::vector<AppLog> logs;

	// Elapsed time between frames
	float elapsed;

	// Max framerate 
	int maxFps;
};

extern Application* App;
#endif
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
class ModuleRenderExercise;
class ModuleGui;
class ModuleProgram;


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
	ModuleRenderExercise* exercise = nullptr;
	ModuleGui* gui = nullptr;
	std::vector<float> fps;
	std::vector<float> milliseconds;
	

private:
	std::list<Module*> modules;
	std::vector<AppLog> logs;

	//Elapsed time between frames
	float elapsed;
	int maxFps;
};

extern Application* App;
#endif
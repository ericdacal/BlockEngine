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

public:
	ModuleRender* renderer = nullptr;
	ModuleWindow* window = nullptr;
	ModuleInput* input = nullptr;
	ModuleProgram* program = nullptr;
	ModuleRenderExercise* exercise = nullptr;
	ModuleGui* gui = nullptr;
	

private:

	std::list<Module*> modules;
	std::vector<AppLog> logs;
	
};

extern Application* App;
#endif
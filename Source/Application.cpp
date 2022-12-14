#pragma once
#include "Application.h"
#include "Modules/ModuleWindow.h"
#include "Modules/ModuleRender.h"
#include "Modules/ModuleInput.h"
#include "Modules/ModuleProgram.h"
#include "Modules/ModuleGui.h"
#include "Modules/ModuleDebugDraw.h"
#include "Modules/ModuleCameraEditor.h"
#include "Modules/ModuleTexture.h"
#include "Modules/ModuleDrawer.h"
#include <math.h>  

using namespace std;

Application::Application()
{
	modules.push_back(window = new ModuleWindow());
	modules.push_back(renderer = new ModuleRender());
	modules.push_back(program = new ModuleProgram());
	modules.push_back(input = new ModuleInput());
	modules.push_back(camEditor = new ModuleCameraEditor());
	modules.push_back(debugDraw = new ModuleDebugDraw());
	modules.push_back(texture= new ModuleTexture());
	modules.push_back(drawer = new ModuleDrawer());
	modules.push_back(gui = new ModuleGui());
}

Application::~Application()
{
	for(list<Module*>::iterator it = modules.begin(); it != modules.end(); ++it)
    {
        delete *it;
    }
}

bool Application::Init()
{
	bool ret = true;

	for(list<Module*>::iterator it = modules.begin(); it != modules.end() && ret; ++it)
		ret = (*it)->Init();

	return ret;
}

update_status Application::Update()
{
	update_status ret = UPDATE_CONTINUE;
	Uint64 start = SDL_GetPerformanceCounter();
	if (fps.size() > 80) fps.erase(fps.begin());
	if (milliseconds.size() > 80) milliseconds.erase(milliseconds.begin());
	for (list<Module*>::iterator it = modules.begin(); it != modules.end() && ret == UPDATE_CONTINUE; ++it)
		ret = (*it)->PreUpdate();

	for (list<Module*>::iterator it = modules.begin(); it != modules.end() && ret == UPDATE_CONTINUE; ++it)
		ret = (*it)->Update();

	for (list<Module*>::iterator it = modules.begin(); it != modules.end() && ret == UPDATE_CONTINUE; ++it)
		ret = (*it)->PostUpdate();
	if (maxFps > 0) {
		float milliseconds_limit = 1000.f / maxFps;
		SDL_Delay(floor(milliseconds_limit - elapsed));
	}
	Uint64 end = SDL_GetPerformanceCounter();
	elapsed = (end - start) / (float)SDL_GetPerformanceFrequency();
	milliseconds.push_back(elapsed * 1000);
	fps.push_back(1.0f / elapsed);
	return ret;
}

void Application::setMaxFrameRate(float maxFps) {
	this->maxFps = maxFps;
}

void Application::NewLog(const char* message, int priority) {
	list<AppLog>::iterator it = appLogs.begin();
	if (appLogs.size() > 1000) appLogs.erase(it);
	// current date/time based on current system
	time_t now = time(0);

	// convert now to string form
	char* dt = ctime(&now);

	struct AppLog tmp = { message, priority, dt };
	appLogs.push_back(tmp);
	
}
void Application::ClearLogs() {
	appLogs.clear();
}


void  Application::RequestBrowser(const char* url) {
	ShellExecute(0, "open", url, 0, 0, 1);
}

std::list<AppLog> Application::GetLogs() {
	return appLogs;
}

bool Application::CleanUp()
{
	bool ret = true;

	for(list<Module*>::reverse_iterator it = modules.rbegin(); it != modules.rend() && ret; ++it)
		ret = (*it)->CleanUp();

	return ret;
}

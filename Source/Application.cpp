#pragma once
#include "Application.h"
#include "Modules/ModuleWindow.h"
#include "Modules/ModuleRender.h"
#include "Modules/ModuleInput.h"
#include "Modules/ModuleProgram.h"
#include "Modules/ModuleRenderExercise.h"
#include "Modules/ModuleGui.h"

using namespace std;

Application::Application()
{
	// Order matters: they will Init/start/update in this order
	modules.push_back(window = new ModuleWindow());
	modules.push_back(renderer = new ModuleRender());
	modules.push_back(input = new ModuleInput());
	modules.push_back(program = new ModuleProgram());
	modules.push_back(exercise = new ModuleRenderExercise());
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

	for(list<Module*>::iterator it = modules.begin(); it != modules.end() && ret == UPDATE_CONTINUE; ++it)
		ret = (*it)->PreUpdate();

	for(list<Module*>::iterator it = modules.begin(); it != modules.end() && ret == UPDATE_CONTINUE; ++it)
		ret = (*it)->Update();

	for(list<Module*>::iterator it = modules.begin(); it != modules.end() && ret == UPDATE_CONTINUE; ++it)
		ret = (*it)->PostUpdate();

	return ret;
}

void Application::NewLog(const char* message, int priority) {
	// current date/time based on current system
	time_t now = time(0);

	// convert now to string form
	char* dt = ctime(&now);

	struct AppLog tmp = { message, priority, dt };
	logs.push_back(tmp);
}

std::vector<AppLog> Application::GetLogs() {
	return logs;
}

bool Application::CleanUp()
{
	bool ret = true;

	for(list<Module*>::reverse_iterator it = modules.rbegin(); it != modules.rend() && ret; ++it)
		ret = (*it)->CleanUp();

	return ret;
}

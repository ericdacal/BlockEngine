#pragma once
#ifndef Gui_Component_h
#define Gui_Component_h

#include "../Globals.h"
#include <imgui.h>
#include <imgui_impl_sdl.h>
#include <imgui_impl_opengl3.h>

class Application;

class GuiComponent
{
public:

	GuiComponent(const char *title)
	{
		this->title = title;
	}

	
	bool Init() {
		ImGui::Begin(this->title);
		return true;
	}


	virtual bool Draw() 
	{
		return true;
	}

	bool Close() {
		ImGui::End();
		return true;
	}
	bool active;

private:
	const char *title;

};
#endif
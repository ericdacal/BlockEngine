#pragma once
#ifndef Module_Gui_h
#define Module_Gui_h


#include "Module.h"

class GuiComponent;
class GuiMenu;
class GuiConsole;
class GuiConfiguration;
class GuiHardware;

class ModuleGui : public Module
{
	public:
		ModuleGui();
		~ModuleGui();
		bool Init();
		update_status PreUpdate();
		update_status Update();
		update_status PostUpdate();
		bool CleanUp();	
		GuiMenu* menu;
		GuiConsole* console;
		GuiConfiguration* config;
		GuiHardware* hardware;
		
	private:
		std::list<GuiComponent*> components;
};
#endif
#pragma once
#ifndef Module_Gui_h
#define Module_Gui_h


#include "Module.h"

class GuiComponent;
class GuiMenu;
class GuiConsole;
class GuiConfiguration;
class GuiHardware;
class GuiAbout;

struct ImFont;

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
		ImFont* AddDefaultFont(float pixel_size);
		GuiMenu* menu;
		GuiConsole* console;
		GuiConfiguration* config;
		GuiHardware* hardware;
		GuiAbout* about;
		
	private:
		std::list<GuiComponent*> components;
};
#endif
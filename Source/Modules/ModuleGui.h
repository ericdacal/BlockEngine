#pragma once
#ifndef Module_Gui_h
#define Module_Gui_h


#include "Module.h"

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
};
#endif
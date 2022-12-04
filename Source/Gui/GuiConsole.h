#pragma once
#ifndef Gui_Console_h
#define Gui_Console_h

#include "GuiComponent.h"
#include <vector>


class GuiConsole : public GuiComponent
{
public:
	
	GuiConsole() : GuiComponent("Console")
	{
	}
	bool Draw();
};
#endif
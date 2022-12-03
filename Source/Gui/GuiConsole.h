#pragma once
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
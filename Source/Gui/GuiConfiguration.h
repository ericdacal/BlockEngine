#pragma once
#ifndef Gui_Configuration_h
#define Gui_Configuration_h

#include "GuiComponent.h"
#include <vector>


class GuiConfiguration : public GuiComponent
{
public:

	GuiConfiguration() : GuiComponent("Configuration")
	{
	}
	bool Draw();
	static bool fullDesktop;
	static bool resizable;
	static bool borderless;
	static float brightness;
	static bool fullscreen;
	static int width;
	static int height;
};
#endif

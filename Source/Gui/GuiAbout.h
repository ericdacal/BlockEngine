#pragma once
#ifndef Gui_About_h
#define Gui_About_h

#include "GuiComponent.h"


class GuiAbout : public GuiComponent
{
public:

	GuiAbout() : GuiComponent("About")
	{
	}
	bool Draw();
};
#endif

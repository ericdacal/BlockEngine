#pragma once
#ifndef Gui_Mesh_h
#define Gui_Mesh_h

#include "GuiComponent.h"


class GuiMesh : public GuiComponent
{
public:

	GuiMesh() : GuiComponent("Mesh Info")
	{
	}
	bool Draw();
};
#endif

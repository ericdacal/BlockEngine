#pragma once
#include "GuiComponent.h"
#include <vector>
#include <GL/glew.h>


class GuiHardware : public GuiComponent
{
public:

	GuiHardware() : GuiComponent("Hardware")
	{
	}
	bool Draw();
private:

	float ToMb(int value);
	int MiBToGb(int value);

	const char* getCaps();

	const ImVec4 YELLOW = ImVec4(1.f, 1.f, 0, 1.f);

};

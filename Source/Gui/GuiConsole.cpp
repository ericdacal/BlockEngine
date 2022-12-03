#include "GuiConsole.h"
#include "GuiComponent.h"
#include "../Application.h"
#include <imgui.h>
#include <list>


bool GuiConsole::Draw() 
{
	ImGui::Text("Block Engine");
	ImGui::Text("This is a project to create a Graphic engine focus in a LEGO style");
	return true;
}
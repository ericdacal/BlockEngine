#include "GuiAbout.h"
#include "../Application.h"
#include "../Modules/ModuleGui.h"
#include <GL/glew.h>
#include <SDL.h>

bool GuiAbout::Draw()
{
	ImGui::Checkbox("Active", &active);
	ImGui::Text("Block Engine");
	ImGui::Text("This is a project to create a Graphic engine focus in a LEGO style");
	ImGui::Separator();
	ImGui::Text("Author: Eric Dacal");
	ImGui::Separator();
	ImGui::Text("Libraries:");
	SDL_version version;
	SDL_GetVersion(&version);
	ImGui::Text("SDL Version:");
	ImGui::SameLine();
	char temp[100];
	sprintf_s(temp, 25, "%d.%d.%d", version.major, version.minor, version.patch);
	ImGui::Text(temp);
	ImGui::Text("OpenGL Version:");
	ImGui::SameLine();
	sprintf_s(temp, 100, "%s", glGetString(GL_VERSION));
	ImGui::Text(temp);
	ImGui::Separator();
	ImGui::Text("License: GPL - 3.0 license");
	return true;
}
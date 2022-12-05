#include "GuiMenu.h"
#include "../Application.h"
#include "../Modules/ModuleGui.h"
#include "GuiConsole.h"
#include "GuiConfiguration.h"

bool GuiMenu::Draw()
{
	// Menu
	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("Help"))
		{
			if (ImGui::MenuItem("Gui Demo")) {}
			if (ImGui::MenuItem("Documentation")) {
				App->RequestBrowser("https://github.com/ericdacal/BlockEngine");
			}
			if (ImGui::MenuItem("Download latest")) {
				App->RequestBrowser("https://github.com/ericdacal/BlockEngine");
			}
			if (ImGui::MenuItem("Report a bug")) {
				App->RequestBrowser("https://github.com/ericdacal/BlockEngine");
			}
			if (ImGui::MenuItem("About")) {}
			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Windows"))
		{
			if (ImGui::Checkbox("Configuration", &App->gui->config->active)) {
			
			}
			if (ImGui::Checkbox("Console", &App->gui->console->active)) {

			}
			ImGui::EndMenu();
		}


		ImGui::EndMainMenuBar();
	}
	return true;
}
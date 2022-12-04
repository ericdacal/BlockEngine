#include "GuiMenu.h"
#include "../Application.h"


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

		ImGui::EndMainMenuBar();
	}
	return true;
}
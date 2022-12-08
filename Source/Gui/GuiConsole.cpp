#include "GuiConsole.h"
#include "GuiComponent.h"
#include "../Application.h"
#include "../Globals.h"
#include <imgui.h>
#include <vector>
#include <ctime>


bool GuiConsole::Draw() 
{
	if (ImGui::Checkbox("Active", &active)) {

	}
	ImGui::SameLine();
	if(ImGui::Button("Clear")) {
		App->ClearLogs();
	}
	std::list<AppLog> logs = App->GetLogs();
	for (std::list<AppLog>::iterator it = logs.begin(); it != logs.end(); ++it) 
	{
		ImVec4 color = ImVec4(1.f, 1.f, 0.f, 1.f);
		ImGui::TextColored(color, it->time);
		ImGui::SameLine();
		ImGui::TextUnformatted(it->message);
	}
	
	return true;
}
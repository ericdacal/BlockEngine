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
	std::vector<AppLog> logs = App->GetLogs();
	for (int i = 0; i < logs.size(); i++)
	{
		ImVec4 color = ImVec4(1.f,1.f,0.f,1.f);
		ImGui::TextColored(color, logs[i].time);
		ImGui::SameLine();
		ImGui::TextUnformatted(logs[i].message);
	}
	return true;
}
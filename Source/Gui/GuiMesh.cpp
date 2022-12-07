#include "GuiMesh.h"

bool GuiMesh::Draw()
{
	ImGui::Checkbox("Active", &active);
	ImGui::Text("Mesh Info");
	return true;
}
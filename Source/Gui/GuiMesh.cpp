#include "GuiMesh.h"
#include "../Application.h"
#include "../Modules/ModuleDrawer.h"
#include "../Model.h"

bool GuiMesh::Draw()
{
	ImGui::Checkbox("Active", &active);
	ImGui::Text("Number of Vertices: %d", App->drawer->getModel().getNumVertices());
	ImGui::Text("Number of Triangles: %d", App->drawer->getModel().getNumTriangles());
	ImGui::Text("Diffuse Texture: %s", App->drawer->getModel().getDiffuseTexture());
	return true;
}
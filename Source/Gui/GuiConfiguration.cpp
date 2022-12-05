#include "GuiConfiguration.h"
#include "GuiComponent.h"
#include "../Modules/ModuleWindow.h"
#include "../Application.h"
#include "imgui.h"
#include <list>


bool GuiConfiguration::fullscreen = false;
float GuiConfiguration::brightness = 1.0f;
int GuiConfiguration::width = 1280;
int GuiConfiguration::height = 720;
int GuiConfiguration::maxFps = 0;

bool GuiConfiguration::fullDesktop = false;
bool GuiConfiguration::resizable = true;
bool GuiConfiguration::borderless = true;



bool GuiConfiguration::Draw()
{
	if (ImGui::CollapsingHeader("Application"))
	{
		char engine[25] = "Block Engine";
		ImGui::InputText("App Name", &engine[0], 25);

		char organization[25] = "Example Organization";
		ImGui::InputText("Organization", &organization[0], 25);

		if (ImGui::SliderInt("Max FPS", &maxFps, 0, 100)) App->setMaxFrameRate(maxFps);

		char title[25];
		sprintf_s(title, 25, "Framerate %.1f", App->fps[App->fps.size() - 1]);
		ImGui::PlotHistogram("##framerate", &App->fps[0], App->fps.size(), 0, title, 0.0f, 100.0f, ImVec2(310, 100));
		sprintf_s(title, 25, "Milliseconds %0.1f", App->milliseconds[App->milliseconds.size() - 1]);
		ImGui::PlotHistogram("##milliseconds", &App->milliseconds[0], App->milliseconds.size(), 0, title, 0.0f, 40.0f, ImVec2(310, 100));		
	}

	if (ImGui::CollapsingHeader("Window"))
	{
		if (ImGui::Checkbox("Active", &active)) {
			
		}
		if(ImGui::SliderFloat("Brightness",&brightness,0.f,1.f))
			App->window->SetBrightness(brightness);
		if (ImGui::SliderInt("Width", &width, 400, 2560))
			App->window->SetWindowSize(width, height);
		if(ImGui::SliderInt("Height", &height, 100, 1080))
			App->window->SetWindowSize(width, height);
		ImGui::Text("Refresh rate: ");
		ImGui::SameLine();
		ImGui::Text("59");
		
		if (ImGui::Checkbox("Fullscreen", &fullscreen)) {
			App->window->SetFullscreen(fullscreen);
		}
		ImGui::SameLine();
		if (ImGui::Checkbox("Resizable", &resizable)) {
			App->window->SetResizable(resizable);

		}
		if (ImGui::Checkbox("Borderless", &borderless)) {
			App->window->SetBorderless(borderless);
		}
		ImGui::SameLine();
		if (ImGui::Checkbox("Full Desktop", &fullDesktop)) {

		}
	}	
	return true;
}
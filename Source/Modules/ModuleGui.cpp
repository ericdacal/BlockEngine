#include "../Application.h"
#include "ModuleGui.h"
#include "ModuleWindow.h"
#include "ModuleRender.h"
#include "../Gui/GuiMenu.h"
#include "../Gui/GuiConsole.h"
#include "../Gui/GuiConfiguration.h"
#include "../Gui/GuiHardware.h"
#include "../Gui/GuiAbout.h"
#include <imgui_impl_sdl.h>





ModuleGui::ModuleGui()
{
}

// Destructor
ModuleGui::~ModuleGui()
{
}



// Called before render is available
bool ModuleGui::Init()
{
	APPLOG("Initializing ImGui");
	App->NewLog("Initializing ImGui", 0);
	const char* glsl_version = "#version 460";
	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	
	// Setup Platform/Renderer backends
	ImGui_ImplSDL2_InitForOpenGL(App->window->window, App->renderer->context);
	ImGui_ImplOpenGL3_Init(glsl_version);
	
	
	menu = new GuiMenu();
	components.push_back(console = new GuiConsole());
	components.push_back(config = new GuiConfiguration());
	components.push_back(hardware = new GuiHardware());
	components.push_back(about = new GuiAbout());


	return true;
}


update_status ModuleGui::PreUpdate() 
{
	// Start the Dear ImGui frame
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame();
	ImGui::NewFrame();

	return UPDATE_CONTINUE;
}


update_status ModuleGui::Update()
{
	bool ret = true;
	menu->Draw();
	for (std::list<GuiComponent*>::iterator it = components.begin(); it != components.end() && ret; ++it) {
		if ((*it)->active) {
			(*it)->Init();
			(*it)->Draw();
			(*it)->Close();
		}
	}
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	return UPDATE_CONTINUE;
}


update_status ModuleGui::PostUpdate()
{
	return UPDATE_CONTINUE;
}



// Called before quitting
bool ModuleGui::CleanUp()
{
	bool ret = true;
	APPLOG("Destroying ImGui elements");
	App->NewLog("Destroying ImGui elements", 0);
	// Cleanup
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();

	return true;
}
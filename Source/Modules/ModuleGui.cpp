#include "../Application.h"
#include "ModuleGui.h"
#include "ModuleWindow.h"
#include "ModuleRender.h"
#include "../Gui/GuiMenu.h"
#include "../Gui/GuiConsole.h"
#include <imgui.h>
#include <imgui_impl_sdl.h>
#include <imgui_impl_opengl3.h>




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
	LOG("Initializing ImGui");
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


	return true;
}


update_status ModuleGui::PreUpdate() 
{

	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		ImGui_ImplSDL2_ProcessEvent(&event);
		if (event.type == SDL_QUIT)
			return UPDATE_STOP;
		if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE && event.window.windowID == SDL_GetWindowID(App->window->window))
			return UPDATE_STOP;
	}

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
		(*it)->Init();
		(*it)->Draw();
		(*it)->Close();
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
	LOG("Destroying ImGui elements");
	App->NewLog("Destroying ImGui elements", 0);
	// Cleanup
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();

	return true;
}
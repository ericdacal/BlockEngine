#include "../Globals.h"
#include "../Application.h"
#include "ModuleWindow.h"

ModuleWindow::ModuleWindow()
{
}

// Destructor
ModuleWindow::~ModuleWindow()
{
}

// Called before render is available
bool ModuleWindow::Init()
{
	APPLOG("Init SDL window & surface");
	App->NewLog("Init SDL window & surface", 0);
	bool ret = true;

	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		APPLOG("SDL_VIDEO could not initialize! SDL_Error: %s\n", SDL_GetError());
		App->NewLog("SDL_VIDEO could not initialize! SDL_Error: %s\n", 0);
		ret = false;
	}
	else
	{
		//Create window
		int width = SCREEN_WIDTH;
		int height = SCREEN_HEIGHT;
		Uint32 flags = SDL_WINDOW_SHOWN |  SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI;

		if(FULLSCREEN == true)
		{
			flags |= SDL_WINDOW_FULLSCREEN;
		}

		window = SDL_CreateWindow(TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, flags);

		if(window == NULL)
		{
			APPLOG("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			App->NewLog("Window could not be created! SDL_Error: %s\n", 0);
			ret = false;
		}
		else
		{
			//Get window surface
			
			screen_surface = SDL_GetWindowSurface(window);
		}
	}

	return ret;
}

bool ModuleWindow::SetResizable(bool resizable)
{
	if (resizable)
		SDL_SetWindowResizable(window, SDL_TRUE);
	else
		SDL_SetWindowResizable(window, SDL_FALSE);
	return true;
}

bool ModuleWindow::SetFullscreen(bool fullscreen)
{
	if (fullscreen)
		SDL_SetWindowFullscreen(window, SDL_TRUE);
	else
		SDL_SetWindowFullscreen(window, SDL_FALSE);
	return true;
}


bool  ModuleWindow::SetBorderless(bool borderless)
{
	if (borderless)
		SDL_SetWindowBordered(window, SDL_FALSE);
	else
		SDL_SetWindowBordered(window, SDL_TRUE);
	return true;
}

bool  ModuleWindow::SetBrightness(float brightness)
{
	SDL_SetWindowBrightness(window, brightness);

	return true;
}
void ModuleWindow::SetWindowSize(int width, int height) {
	SDL_SetWindowSize(window, width, height);
}




// Called before quitting
bool ModuleWindow::CleanUp()
{
	APPLOG("Destroying SDL window and quitting all SDL systems");
	App->NewLog("Destroying SDL window and quitting all SDL systems", 0);

	//Destroy window
	if(window != NULL)
	{
		SDL_DestroyWindow(window);
	}

	//Quit SDL subsystems
	SDL_Quit();
	return true;
}


#include "../Globals.h"
#include "../Application.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleCameraEditor.h"
#include "../SDL/include/SDL.h"

ModuleInput::ModuleInput()
{}

// Destructor
ModuleInput::~ModuleInput()
{}

// Called before render is available
bool ModuleInput::Init()
{
	APPLOG("Init SDL input event system");
    App->NewLog("Init SDL input event system", 0);
	bool ret = true;
	SDL_Init(0);

	if(SDL_InitSubSystem(SDL_INIT_EVENTS) < 0)
	{
		APPLOG("SDL_EVENTS could not initialize! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}

	return ret;
}

// Called every draw update
update_status ModuleInput::Update()
{
    // Computation of deltaTime
    Uint64 currentFrame = SDL_GetPerformanceCounter();

    deltaTime = (double)((currentFrame - lastFrame) * 1000 / (double)SDL_GetPerformanceFrequency());
    lastFrame = currentFrame;

    float currentSpeed = (cameraSpeed * deltaTime);
    Frustum* f = App->camEditor->GetFustrum();

    float3 up = f->up;
    float3 pos = f->pos;
    
    keyboard = SDL_GetKeyboardState(NULL);

    if (keyboard[SDL_SCANCODE_Q]) {
        f->pos = (pos + (up * currentSpeed));
        App->camEditor->ReloadViewMatrix();
    }

    if (keyboard[SDL_SCANCODE_E]) {
        f->pos = (pos - (up * currentSpeed));
        App->camEditor->ReloadViewMatrix();
    }


    SDL_Event sdlEvent;
    while (SDL_PollEvent(&sdlEvent) != 0)
    {
        switch (sdlEvent.type)
        {
            case SDL_QUIT:
                return UPDATE_STOP;
            case SDL_WINDOWEVENT:
                if (sdlEvent.window.event == SDL_WINDOWEVENT_RESIZED || sdlEvent.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
                    App->renderer->WindowResized(sdlEvent.window.data1, sdlEvent.window.data2);
                break;
        }
    }

    return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleInput::CleanUp()
{
	APPLOG("Quitting SDL input event subsystem");
    App->NewLog("Quitting SDL input event subsystem", 0);
	SDL_QuitSubSystem(SDL_INIT_EVENTS);
	return true;
}

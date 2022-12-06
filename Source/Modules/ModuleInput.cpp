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
    float3 front = f->front;
    float3 worldRight = f->WorldRight();
    
    keyboard = SDL_GetKeyboardState(NULL);

    if (keyboard[SDL_SCANCODE_Q]) {
        f->pos = (pos + (up * currentSpeed));
        App->camEditor->ReloadViewMatrix();
    }

    if (keyboard[SDL_SCANCODE_E]) {
        f->pos = (pos - (up * currentSpeed));
        App->camEditor->ReloadViewMatrix();
    }

    if (keyboard[SDL_SCANCODE_W]) {
        f->pos = (pos + (front * currentSpeed));
        App->camEditor->ReloadViewMatrix();
    }

    if (keyboard[SDL_SCANCODE_S]) {
        f->pos = (pos - (front * currentSpeed));
        App->camEditor->ReloadViewMatrix();
    }

    if (keyboard[SDL_SCANCODE_D]) {
        f->pos = (pos + (worldRight * currentSpeed));
        App->camEditor->ReloadViewMatrix();
    }

    if (keyboard[SDL_SCANCODE_A]) {
        f->pos = (pos - (worldRight * currentSpeed));
        App->camEditor->ReloadViewMatrix();
    }
    if (keyboard[SDL_SCANCODE_UP]) {
        float3x3 rotationDeltaMatrix = float3x3::identity;
        rotationDeltaMatrix = rotationDeltaMatrix.RotateX(0.01f * currentSpeed);
        float3 oldFront = f->front.Normalized();
        f->front = (rotationDeltaMatrix.MulDir(oldFront));
        float3 oldUp = f->up.Normalized();
        f->up = (rotationDeltaMatrix.MulDir(oldUp));
        App->camEditor->ReloadViewMatrix();
    }
    if (keyboard[SDL_SCANCODE_DOWN]) {
        float3x3 rotationDeltaMatrix = float3x3::identity;
        rotationDeltaMatrix = rotationDeltaMatrix.RotateX(-0.01f * currentSpeed);
        float3 oldFront = f->front.Normalized();
        f->front = (rotationDeltaMatrix.MulDir(oldFront));
        float3 oldUp = f->up.Normalized();
        f->up = (rotationDeltaMatrix.MulDir(oldUp));
        App->camEditor->ReloadViewMatrix();
    }
    if (keyboard[SDL_SCANCODE_RIGHT]) {
        float3x3 rotationDeltaMatrix = float3x3::identity;
        rotationDeltaMatrix = rotationDeltaMatrix.RotateY(-0.01f * currentSpeed);
        float3 oldFront = f->front.Normalized();
        f->front = (rotationDeltaMatrix.MulDir(oldFront));
        float3 oldUp = f->up.Normalized();
        f->up = (rotationDeltaMatrix.MulDir(oldUp));
        App->camEditor->ReloadViewMatrix();
    }
    if (keyboard[SDL_SCANCODE_LEFT]) {
        float3x3 rotationDeltaMatrix = float3x3::identity;
        rotationDeltaMatrix = rotationDeltaMatrix.RotateY(0.01f * currentSpeed);
        float3 oldFront = f->front.Normalized();
        f->front = (rotationDeltaMatrix.MulDir(oldFront));
        float3 oldUp = f->up.Normalized();
        f->up = (rotationDeltaMatrix.MulDir(oldUp));
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

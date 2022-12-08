#include "../Globals.h"
#include "../Application.h"
#include "ModuleDrawer.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleCameraEditor.h"
#include "../SDL/include/SDL.h"
#include <imgui_impl_sdl.h>

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
    shiftButton = false;
    leftAltButton = false;
    leftMouseButton = false;
    rightMouseButton = false;
    // Computation of deltaTime
    Uint64 currentFrame = SDL_GetPerformanceCounter();

    deltaTime = (double)((currentFrame - lastFrame) * 1000 / (double)SDL_GetPerformanceFrequency());
    lastFrame = currentFrame;

    
    SDL_Event sdlEvent;
    Frustum* f = App->camEditor->GetFustrum();

    float3 up = f->up;
    float3 pos = f->pos;
    float3 front = f->front;
    float3 worldRight = f->WorldRight();
    
    keyboard = SDL_GetKeyboardState(NULL);

    Uint32 buttons = SDL_GetMouseState(NULL, NULL);

    if (buttons & SDL_BUTTON(1)) {
        leftMouseButton = true;
    }
    if (buttons & SDL_BUTTON(3)) {
        rightMouseButton = true;
    }

    if (keyboard[SDL_SCANCODE_LSHIFT]) {
        cameraSpeed = 0.1;
    }
    else cameraSpeed = 0.05;

    float currentSpeed = (cameraSpeed * deltaTime);

    if (keyboard[SDL_SCANCODE_Q] && rightMouseButton) {
        f->pos = (pos + (up * currentSpeed));
        App->camEditor->changeCameraMode(0);
        App->camEditor->ReloadViewMatrix();
    }

    if (keyboard[SDL_SCANCODE_E] && rightMouseButton) {
        f->pos = (pos - (up * currentSpeed));
        App->camEditor->changeCameraMode(0);
        App->camEditor->ReloadViewMatrix();
    }

    if (keyboard[SDL_SCANCODE_W] && rightMouseButton) {
        f->pos = (pos + (front * currentSpeed));
        App->camEditor->changeCameraMode(0);
        App->camEditor->ReloadViewMatrix();
    }

    if (keyboard[SDL_SCANCODE_S] && rightMouseButton) {
        f->pos = (pos - (front * currentSpeed));
        App->camEditor->changeCameraMode(0);
        App->camEditor->ReloadViewMatrix();
    }

    if (keyboard[SDL_SCANCODE_D] && rightMouseButton) {
        f->pos = (pos + (worldRight * currentSpeed));
        App->camEditor->changeCameraMode(0);
        App->camEditor->ReloadViewMatrix();
    }

    if (keyboard[SDL_SCANCODE_A] && rightMouseButton) {
        f->pos = (pos - (worldRight * currentSpeed));
        App->camEditor->changeCameraMode(0);
        App->camEditor->ReloadViewMatrix();
    }

    if (keyboard[SDL_SCANCODE_UP] && rightMouseButton) {
        float3x3 rotationDeltaMatrix = float3x3::identity;
        rotationDeltaMatrix = rotationDeltaMatrix.RotateX(0.01f * currentSpeed);
        float3 oldFront = f->front.Normalized();
        f->front = (rotationDeltaMatrix.MulDir(oldFront));
        float3 oldUp = f->up.Normalized();
        f->up = (rotationDeltaMatrix.MulDir(oldUp));
        App->camEditor->changeCameraMode(0);
        App->camEditor->ReloadViewMatrix();
    }
    if (keyboard[SDL_SCANCODE_DOWN] && rightMouseButton) {
        float3x3 rotationDeltaMatrix = float3x3::identity;
        rotationDeltaMatrix = rotationDeltaMatrix.RotateX(-0.01f * currentSpeed);
        float3 oldFront = f->front.Normalized();
        f->front = (rotationDeltaMatrix.MulDir(oldFront));
        float3 oldUp = f->up.Normalized();
        f->up = (rotationDeltaMatrix.MulDir(oldUp));
        App->camEditor->changeCameraMode(0);
        App->camEditor->ReloadViewMatrix();
    }
    if (keyboard[SDL_SCANCODE_RIGHT] && rightMouseButton) {
        float3x3 rotationDeltaMatrix = float3x3::identity;
        rotationDeltaMatrix = rotationDeltaMatrix.RotateY(-0.01f * currentSpeed);
        float3 oldFront = f->front.Normalized();
        f->front = (rotationDeltaMatrix.MulDir(oldFront));
        float3 oldUp = f->up.Normalized();
        f->up = (rotationDeltaMatrix.MulDir(oldUp));
        App->camEditor->changeCameraMode(0);
        App->camEditor->ReloadViewMatrix();
    }
    if (keyboard[SDL_SCANCODE_LEFT] && rightMouseButton) {
        float3x3 rotationDeltaMatrix = float3x3::identity;
        rotationDeltaMatrix = rotationDeltaMatrix.RotateY(0.01f * currentSpeed);
        float3 oldFront = f->front.Normalized();
        f->front = (rotationDeltaMatrix.MulDir(oldFront));
        float3 oldUp = f->up.Normalized();
        f->up = (rotationDeltaMatrix.MulDir(oldUp));
        App->camEditor->changeCameraMode(0);
        App->camEditor->ReloadViewMatrix();
    }
    if (keyboard[SDL_SCANCODE_LALT]) {
        leftAltButton = true;
    }
   
    
    while (SDL_PollEvent(&sdlEvent) != 0)
    {
        if (!leftMouseButton or !leftAltButton) {
            SDL_SetRelativeMouseMode(SDL_FALSE);
            App->camEditor->changeCameraMode(0);
        }
        ImGui_ImplSDL2_ProcessEvent(&sdlEvent);
        switch (sdlEvent.type)
        {
            case SDL_QUIT:
                return UPDATE_STOP;
                break;
            case SDL_WINDOWEVENT:
                if (sdlEvent.window.event == SDL_WINDOWEVENT_RESIZED || sdlEvent.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
                    App->renderer->WindowResized(sdlEvent.window.data1, sdlEvent.window.data2);
                break;
            case SDL_MOUSEWHEEL:
                if (leftMouseButton && leftAltButton) {
                    App->camEditor->zoom(-sdlEvent.wheel.y);
                    App->camEditor->ReloadViewMatrix();
                }
                break;
            case SDL_MOUSEMOTION:
                if (leftMouseButton && leftAltButton) {
                    SDL_SetRelativeMouseMode(SDL_TRUE);
                    App->camEditor->changeCameraMode(1);
                    App->camEditor->rotateAzimuth(sdlEvent.motion.xrel * 0.001);
                    App->camEditor->rotatePolar(sdlEvent.motion.yrel * 0.001);
                    App->camEditor->ReloadViewMatrix();
                }
                break;
            case SDL_DROPFILE:
                App->drawer->changeModel(sdlEvent.drop.file);
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

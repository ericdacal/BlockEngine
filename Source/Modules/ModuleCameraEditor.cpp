#include "ModuleCameraEditor.h"
#include "../Application.h"
#include "ModuleWindow.h"
#include "Math/float3.h"
#include "Math/float3x3.h"
#include "Math/float3x4.h"
#include "Math/MathConstants.h"
#include <SDL.h>

ModuleCameraEditor::ModuleCameraEditor()
{}

// Destructor
ModuleCameraEditor::~ModuleCameraEditor()
{}




// Called before render is available
bool ModuleCameraEditor::Init()
{
    //SDL_SetHintWithPriority(SDL_HINT_MOUSE_RELATIVE_MODE_WARP, "1", SDL_HINT_OVERRIDE);
   
    APPLOG("Creating camera matrix, view and projection");
    bool ret = true;

    f.pos = float3(0.0f, 1.0f, 8.0f);
    f.front = -float3::unitZ;
    f.up = float3::unitY;
    mode = 0;

    f.nearPlaneDistance = 0.1f;
    f.farPlaneDistance = 100.0f;

    int width;
    int height;
    SDL_GetWindowSize(App->window->window, &width, &height);
  
    SetFOV(width, height);
    ReloadViewMatrix();

    view = GetViewMatrix(); 
    proj = GetProjectionMatrix();

    return ret;
}

// Called every draw update
update_status ModuleCameraEditor::Update()
{
    return UPDATE_CONTINUE;
}

void ModuleCameraEditor::SetFOV(int width, int height) {
    f.verticalFov = pi / 4.0f;
   
    SetAspectRatio(width, height);
    f.horizontalFov = 2.f * atanf(tanf(f.verticalFov * 0.5f) * aspect);

    f.type = FrustumType::PerspectiveFrustum;
}

void ModuleCameraEditor::SetAspectRatio(int width, int height) {
    SDL_GetWindowSize(App->window->window, &width, &height);

    aspect = (float)width / (float)height;
}

Frustum* ModuleCameraEditor::GetFustrum() {
    return &f;
}

// Called before quitting
bool ModuleCameraEditor::CleanUp()
{
    return true;
}


float4x4 ModuleCameraEditor::GetProjectionMatrix() {
    return f.ProjectionMatrix();
}



float4x4 ModuleCameraEditor::LookAt(float3 eye, float3 at, float3 up)
{
    float3 zaxis = (at - eye).Normalized();
    float3 xaxis = (zaxis.Cross(up)).Normalized();
    float3 yaxis = xaxis.Cross(zaxis);
    zaxis = zaxis.Neg();
   
    float4x4 viewMatrix = float4x4(xaxis.x, xaxis.y, xaxis.z, -xaxis.Dot(eye),
        yaxis.x, yaxis.y, yaxis.z, -yaxis.Dot(eye),
        zaxis.x, zaxis.y, zaxis.z, -zaxis.Dot(eye),
        0, 0, 0, 1);
    return viewMatrix;
}


float4x4 ModuleCameraEditor::GetViewMatrix() {
    return view;
}

void ModuleCameraEditor::ReloadViewMatrix() {
    if (mode == 0) view = f.ViewMatrix();
    else view = LookAt(f.pos, float3(0.f, 0.f, 0.f), float3::unitY);
}
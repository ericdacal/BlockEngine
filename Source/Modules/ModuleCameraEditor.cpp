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

    f.pos = float3::zero;
    f.front = -float3::unitZ;
    f.up = float3::unitY;

    f.nearPlaneDistance = 0.1f;
    f.farPlaneDistance = 100.0f;
  
    SetFOV();

    f.type = FrustumType::PerspectiveFrustum;


    float4x4 model = float4x4::FromTRS(float3(2.0f, 0.0f, 0.0f), float4x4::RotateZ(pi / 4.0f), float3(2.0f, 1.0f, 0.0f));
    view = LookAt(float3(0.0f, 4.0f, 8.0f), float3(0.0f, 0.0f, 0.0f), float3::unitY);
    proj = GetProjectionMatrix();


    return ret;
}

// Called every draw update
update_status ModuleCameraEditor::Update()
{
    return UPDATE_CONTINUE;
}

void ModuleCameraEditor::SetFOV() {
    f.verticalFov = pi / 4.0f;
    SetAspectRatio();
    f.horizontalFov = 2.f * atanf(tanf(f.verticalFov * 0.5f) * aspect);
}

void ModuleCameraEditor::SetAspectRatio() {
    int width;
    int height;
    SDL_GetWindowSize(App->window->window, &width, &height);

    float aspect = (float)width / (float)height;
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
    float4x4 view = LookAt(f.pos, float3(0.f, 0.f, 0.f), float3::unitY);
    return view;
}
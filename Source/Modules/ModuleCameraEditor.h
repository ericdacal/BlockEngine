#pragma once
#ifndef Module_Camera_Editor_h
#define Module_Camera_Editor_h

#include "Math/float4x4.h"
#include "Geometry/Frustum.h"

#include "Module.h"

typedef unsigned __int8 Uint8;


class ModuleCameraEditor : public Module
{
public:

	ModuleCameraEditor();
	~ModuleCameraEditor();

	bool Init();
	update_status Update();
	bool CleanUp();

	void SetFOV();
	void SetAspectRatio();
	float4x4 GetProjectionMatrix();
	float4x4 GetViewMatrix();

private:
	// LookAt glm approach
	float4x4 LookAt(float3 eye, float3 at, float3 up);
	
	// Aspect ratio of the screen
	float aspect;
	
	// View and projection matrix
	float4x4 view, proj;

	Frustum f;
};
#endif
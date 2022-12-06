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
	void SetPlaneDistances();
	Frustum* GetFustrum();
	float4x4 GetProjectionMatrix();
	float4x4 GetViewMatrix();

private:
	float4x4 LookAt(float3 eye, float3 at, float3 up);
	Frustum f;
	float4x4 view, proj;
};
#endif
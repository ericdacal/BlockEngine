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

	void SetFOV(int width, int height);
	void SetAspectRatio(int width, int height);
	float4x4 GetProjectionMatrix();
	float4x4 GetViewMatrix();
	void changeCameraMode(int mode);
	Frustum* GetFustrum();
	void ReloadViewMatrix();
	void RotatePitch(float units);
	void RotateYaw(float units);

	// Function to orbit camara
	void zoom(const float units);
	void rotateAzimuth(const float radians);
	void rotatePolar(const float radians);

private:

	// Spherical coordinates 
	float3 center;
	float radius; // Radius of the orbit camera sphere
	float minRadius; // Minimal radius of the orbit camera sphere (cannot fall below this value)
	float maxRadius;
	float azimuthAngle; // Azimuth angle on the orbit camera sphere
	float polarAngle; // Polar angle on the orbit camera sphere
	float3 getPositionCartesian();
	void getSphericalAngles();
	float toRadians(float degrees);
	float toDegrees(float radians);

	// LookAt glm approach
	float4x4 LookAt(float3 eye, float3 at, float3 up);
	
	// Aspect ratio of the screen
	float aspect;

	// Camera mode, 0 for moving camera, 1 for orbital camera
	int mode;

	// View and projection matrix
	float4x4 view, proj;

	Frustum f;

};
#endif
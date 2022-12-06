#pragma once
#include "Module.h"
#include "../Globals.h"
#include <DirectXTex.h>


class ModuleTexture : public Module
{
public:

	ModuleTexture();
	~ModuleTexture();

	bool Init();

	const DirectX::ScratchImage* Load(const char* filePath);

private:
	DirectX::ScratchImage* LoadTextureCPU(const WCHAR* filePath);
};
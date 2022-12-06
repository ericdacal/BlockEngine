#include "ModuleTexture.h"
#include "../Application.h"
using namespace std;

ModuleTexture::ModuleTexture()
{}

// Destructor
ModuleTexture::~ModuleTexture()
{}

bool ModuleTexture::Init() {
	return true;
}

const DirectX::ScratchImage * ModuleTexture::Load(const char* filePath) {
	APPLOG("Loading Textures");
	App->NewLog("Loading Texture:", 0);
	APPLOG(filePath);
	wchar_t* file = new wchar_t[strlen(filePath) + 1];
	mbstowcs_s(NULL, file, strlen(filePath) + 1, filePath, strlen(filePath));
	return LoadTextureCPU(file);
}


DirectX::ScratchImage* ModuleTexture::LoadTextureCPU(const WCHAR* filePath) {
	APPLOG("filePath: %s", filePath);
	DirectX::ScratchImage* imageData = new DirectX::ScratchImage();
	HRESULT dssResult = DirectX::LoadFromDDSFile(filePath, DirectX::DDS_FLAGS_NONE, nullptr, *imageData);
	if (FAILED(dssResult)) {
		APPLOG("NO DSS File");
		HRESULT tgaResult = DirectX::LoadFromTGAFile(filePath, DirectX::TGA_FLAGS_NONE, nullptr, *imageData);
		if (FAILED(tgaResult)) {
			APPLOG("NO TGA File");
			HRESULT wicResult = DirectX::LoadFromWICFile(filePath, DirectX::WIC_FLAGS_NONE, nullptr, *imageData);
			if (FAILED(wicResult)) {
				APPLOG("NO WIC File");
				assert("Texture with no supported format");
				return NULL;
			}
		}
	}
	DirectX::ScratchImage* destImage = new DirectX::ScratchImage();
	HRESULT flipResult = DirectX::FlipRotate(imageData->GetImages(), imageData->GetImageCount(), imageData->GetMetadata(), DirectX::TEX_FR_FLIP_VERTICAL, *destImage);
	if (FAILED(flipResult)) {
		APPLOG("Error Flip Image");
		assert("Error Flipping Image");
		return NULL;
	}
	return destImage;
}
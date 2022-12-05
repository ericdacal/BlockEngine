#include "GuiHardware.h"
#include "SDL.h"
#include "../Application.h"
#include <iostream>
#include <math.h>
#include <string>





const char* GuiHardware::getCaps() {
	char temp[200] = "";

	if (SDL_Has3DNow()) 
	{
		sprintf_s(temp, 200, "3DNOW");
	}
	
	if (SDL_HasAltiVec()) 
	{
		if (std::strlen(temp) > 0) {
			sprintf_s(temp, 200, "%s, AltiVec", temp);
		}
		else sprintf_s(temp, 200, "AltiVec");
	}
	if (SDL_HasAVX())
	{
		if (std::strlen(temp) > 0) {
			sprintf_s(temp, 200, "%s, AVX", temp);
		}
		else sprintf_s(temp, 200, "AVX");
	}
	
	if (SDL_HasAVX2){
		if (std::strlen(temp) > 0) {
			sprintf_s(temp, 200, "%s, AVX2", temp);
		}
		else sprintf_s(temp, 200, "AVX2");
	}

	if(SDL_HasMMX())
	{
		if (std::strlen(temp) > 0) {
			sprintf_s(temp, 200, "%s, MMX", temp);
		}
		else sprintf_s(temp, 200, "MMX");
	}
	if (SDL_HasRDTSC())
	{
		if (std::strlen(temp) > 0) {
			sprintf_s(temp, 200, "%s, RDTSC", temp);
		}
		else sprintf_s(temp, 200, "RDTSC");
	}
	if (SDL_HasSSE()) 
	{
		if (std::strlen(temp) > 0) {
			sprintf_s(temp, 200, "%s, SSE", temp);
		}
		else sprintf_s(temp, 200, "SSE");
	}
	if (SDL_HasSSE2()) 
	{
		if (std::strlen(temp) > 0) {
			sprintf_s(temp, 200, "%s, SSE2", temp);
		}
		else sprintf_s(temp, 200, "SSE2");
	}
	if(SDL_HasSSE3()) 
	{
		if (std::strlen(temp) > 0) {
			sprintf_s(temp, 200, "%s, SSE3", temp);
		}
		else sprintf_s(temp, 200, "SSE3");
	}
	if(SDL_HasSSE41())
	{
		if (std::strlen(temp) > 0) {
			sprintf_s(temp, 200, "%s, SSE41", temp);
		}
		else sprintf_s(temp, 200, "SSE41");
	}
	if(SDL_HasSSE42()) 
	{
		if (std::strlen(temp) > 0) {
			sprintf_s(temp, 200, "%s, SSE42", temp);
		}
		else sprintf_s(temp, 200, "SSE42");
	}
	return temp;
}


float GuiHardware::ToMb(int value) {
	return (value / 1024.f);
}

int GuiHardware::MiBToGb(int value) {
	return round(((float)value / 1024.f));
}



bool GuiHardware::Draw()
{
	SDL_version version;
	SDL_GetVersion(&version);

	if (ImGui::Checkbox("Active", &active)) {

	}
	
	ImGui::Text("SDL Version:");
	ImGui::SameLine();
	char temp[100];
	sprintf_s(temp, 25, "%d.%d.%d", version.major, version.minor, version.patch);
	ImGui::TextColored(YELLOW,temp);


	ImGui::Text("OpenGL Version:");
	ImGui::SameLine();
	sprintf_s(temp, 100, "%s", glGetString(GL_VERSION));
	ImGui::TextColored(YELLOW, temp);

	ImGui::Separator();
	
	ImGui::Text("CPUs:");
	ImGui::SameLine();
	sprintf_s(temp, 25, "%d", SDL_GetCPUCount());
	ImGui::TextColored(YELLOW, temp);
	ImGui::SameLine();
	ImGui::TextColored(YELLOW, "(Cache: %d kb)", SDL_GetCPUCacheLineSize());

	
	ImGui::Text("System RAR:");
	ImGui::SameLine();
	sprintf_s(temp, 25, "%d Gb", MiBToGb(SDL_GetSystemRAM()));
	ImGui::TextColored(YELLOW, temp);


	ImGui::Text("Caps:");
	ImGui::SameLine();
	const char* caps = getCaps();
	ImGui::TextColored(YELLOW, caps);
	
	
	ImGui::Separator();
	ImGui::Text("GPU: ");
	ImGui::SameLine();
	sprintf_s(temp, 100, "%s", glGetString(GL_VENDOR));
	ImGui::TextColored(YELLOW, temp);
	

	ImGui::Text("Brand: ");
	ImGui::SameLine();
	sprintf_s(temp, 100, "%s", glGetString(GL_RENDERER));
	ImGui::TextColored(YELLOW, temp);
	const char* brand = temp;

	if (strcmp(brand, "NVIDIA Corporation")) {
		


		int vramBudget;
		glGetIntegerv(GL_GPU_MEMORY_INFO_TOTAL_AVAILABLE_MEMORY_NVX, &vramBudget);
		int vramAvailable;
		glGetIntegerv(GL_GPU_MEMORY_INFO_CURRENT_AVAILABLE_VIDMEM_NVX, &vramAvailable);

		ImGui::Text("VRAM Budget: ");
		ImGui::SameLine();
		sprintf_s(temp, 100, "%f Mb", ToMb(vramBudget));
		ImGui::TextColored(YELLOW, temp);


		ImGui::Text("VRAM Usage: ");
		ImGui::SameLine();
		sprintf_s(temp, 100, "%f Mb", ToMb(vramBudget - vramAvailable));
		ImGui::TextColored(YELLOW, temp);

		glGetIntegerv(GL_GPU_MEMORY_INFO_CURRENT_AVAILABLE_VIDMEM_NVX, &vramAvailable);
		ImGui::Text("VRAM Available: ");
		ImGui::SameLine();
		sprintf_s(temp, 100, "%f Mb", ToMb(vramAvailable));
		ImGui::TextColored(YELLOW, temp);

		int vramDedicated;
		glGetIntegerv(GL_GPU_MEMORY_INFO_DEDICATED_VIDMEM_NVX, &vramDedicated);


		ImGui::Text("VRAM Dedicated: ");
		ImGui::SameLine();
		sprintf_s(temp, 100, "%f Mb", ToMb(vramDedicated));
		ImGui::TextColored(YELLOW, temp);
	
	}
	else {
		LOG("Unknown GPU vendor");
		App->NewLog("Unknown GPU vendor", 1);
	}
		
	return true;
}



	
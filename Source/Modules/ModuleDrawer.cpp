#include "ModuleDrawer.h"
#include "../Application.h"
#include "ModuleWindow.h"
#include "ModuleGui.h"
#include "../Gui/GuiMesh.h"
#include "SDL.h"



ModuleDrawer::ModuleDrawer()
{
}

// Destructor
ModuleDrawer::~ModuleDrawer()
{
}

bool ModuleDrawer::Init() {
	bool ret = true;
	
	m = Model();
	m.Load("../Game/assets/resources/BakerHouse.fbx");
	return true;
}

update_status ModuleDrawer::PreUpdate()
{

	update_status ret = UPDATE_CONTINUE;
	
	return ret;
}


update_status ModuleDrawer::Update()
{
	update_status ret = UPDATE_CONTINUE;
	m.Draw();

	return ret;
}

Model  ModuleDrawer::getModel() {
	return m;
}

void ModuleDrawer::changeModel(const char* path) {
	m = Model();
	m.Load(path);
}

#pragma once
#ifndef Module_Drawer_h
#define Module_Drawer_h

#include "Module.h"
#include "../Model.h"


class ModuleDrawer : public Module
{
public:
	ModuleDrawer();
	~ModuleDrawer();
	void changeModel(const char* path);
	bool Init();
	update_status PreUpdate();
	update_status Update();


private:
	Model m;
	int num_vertices;
	int num_triangles;

};
#endif
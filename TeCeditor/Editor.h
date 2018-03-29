#pragma once
#include"CameraManager.h"
#include"DistantView.h"
#include"MiddleView.h"
#include "Object.h"

class Editor {
public:
	Editor();
	void update();
	void draw();
	CameraManager camera;
	DistantView Dview;
	MiddleView Mview;
	ObjectManager objmanager;
};
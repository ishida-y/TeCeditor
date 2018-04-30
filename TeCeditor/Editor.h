#pragma once
#include<Siv3D.hpp>
#include"CameraManager.h"
#include "BackGroundManager.h"
#include "Operator.h"
#include "ObjectManager.h"

class Editor {
public:
	Editor();
	void update();
	void draw();
private:
	CameraManager camera;
	BackGroundManager Dview;
	BackGroundManager Mview;
	ObjectManager Obj;
	GUI gui;
	bool lookGui;
};
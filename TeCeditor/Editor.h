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
	~Editor();
private:
	CameraManager camera;
	BackGroundManager Dview;
	BackGroundManager Mview;
	ObjectManager Obj1;
	ObjectManager Obj2;
	GUI gui;
	bool lookGui;
};
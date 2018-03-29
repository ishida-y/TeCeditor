#pragma once
#include<Siv3D.hpp>

class CameraManager {
public:
	CameraManager();
	void update();
	Vec2 pos;
	double scale;
};
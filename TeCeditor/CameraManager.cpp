#include"CameraManager.h"
#include<Siv3D.hpp>

CameraManager::CameraManager() :
	pos(0, 0),
	scale(1.0) {
}

void CameraManager::update() {
	if (Input::MouseM.pressed) {
		//位置
		pos -= Vec2((double)Mouse::Delta().x, (double)Mouse::Delta().y);
		//ズーム
		if (Mouse::Wheel() < 0) {
			scale += 0.2;
		}
		else if (Mouse::Wheel() > 0 && scale > 0.3) {
			scale -= 0.2;
		}
	}

	//キー操作
	const static int speed = 15;
	if (Input::KeyRight.pressed) {
		pos.x += speed;
	}
	if (Input::KeyLeft.pressed) {
		pos.x -= speed;
	}
	if (Input::KeyUp.pressed) {
		pos.y -= speed;
	}
	if (Input::KeyDown.pressed) {
		pos.y += speed;
	}

	Print(L"CameraPos:");
	Println(pos);
	Print(L"Zoom:");
	Println(scale);
}
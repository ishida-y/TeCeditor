#include"CameraManager.h"
#include<Siv3D.hpp>

CameraManager::CameraManager() :
	pos(0.0, 0.0),
	scale(1.0) {
	pos = Window::Center();
}

void CameraManager::update() {
	//�ʒu
	if (Input::MouseM.pressed) {
		pos += Vec2((double)Mouse::Delta().x / scale, (double)Mouse::Delta().y / scale);

		//�Y�[��
		if (Mouse::Wheel() < 0) {
			scale += 0.2;
		}
		else if (Mouse::Wheel() > 0 && scale > 0.3) {
			scale -= 0.2;
		}
	}


	Print(L"CameraPos:");
	Println(pos);
	Print(L"Zoom:");
	Println(scale);
}
#include "Editor.h"
#include<Siv3D.hpp>

Editor::Editor() {
}

void Editor::update() {
	const Transformer2D transformer(Mat3x2::Translate(camera.pos).scale(camera.scale, { 640, 360 }), true);
	
	Print(L"MousePos:");
	Println(Mouse::Pos());
	Print(L"Zoom:");
	Println(camera.scale);

	camera.update();
	objmanager.update();

}

void Editor::draw() {

	const Transformer2D transformer(Mat3x2::Translate(camera.pos).scale(camera.scale, { 640, 360 }), true);
	Println(camera.pos);
	Dview.draw(camera.pos);
	Mview.draw(camera.pos);
	objmanager.draw();
	
}
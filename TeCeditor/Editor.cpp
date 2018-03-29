#include "Editor.h"
#include<Siv3D.hpp>

Editor::Editor() :
	objmanager(L"obj") {
}

void Editor::update() {
	const Transformer2D transformer(Mat3x2::Translate(camera.pos).scale(camera.scale, { 640, 360 }), true);

	Print(L"MousePos:");
	Println(Mouse::Pos());

	camera.update();
	objmanager.update();

}

void Editor::draw() {
	const Transformer2D transformer(Mat3x2::Translate(camera.pos).scale(camera.scale, { 640, 360 }), true);
	Println(camera.pos);
	Dview.draw(camera.pos);
	Mview.draw(camera.pos);
	objmanager.draw();

	//ŽG‚ÉƒOƒŠƒbƒh
	int GridSize = 100;
	if (camera.scale < 0.6) GridSize = 250;
	int mouseX = ((int)(Mouse::Pos().x / GridSize) * GridSize);
	for (int y = -10; y < 10; y++) {
		for (int x = -30; x < 30; x++) {
			Rect dot(mouseX + x*GridSize, y*GridSize, GridSize);
			dot.drawFrame(1.0, 1.0, Color(128, 128, 128, 128));
		}
	}
	Line(Vec2(mouseX - 10000, 0), Vec2(mouseX + 10000, 0)).draw(3.0, Palette::Red);
}
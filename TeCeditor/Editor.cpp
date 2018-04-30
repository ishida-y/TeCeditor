#include "Editor.h"

Editor::Editor() :
	Mview(L"MiddleView", Vec2(0.4, 0.3)),
	Dview(L"DistantView", Vec2(0.2, 0.2)),
	Obj(L"obj"),
	gui(GUIStyle::Default),
	lookGui(true) {
	//gui設定
	gui.setPos(0, 100);
	gui.setTitle(L"mode");
	gui.add(L"mood", GUIRadioButton::Create({ L"None",L"Dview", L"Mview", L"Obj" }, 0, true));
	gui.show(true);
	TextureAsset::Register(L"BackGround", L"Data/BackGround.png");
}

void Editor::update() {
	const Transformer2D transformer(Mat3x2::Translate(-camera.pos + Window::Center()).scale(camera.scale, { 640, 360 }), true);
	Print(L"MousePos:");
	Println(Mouse::Pos());

	camera.update();

	if (Input::KeySpace.clicked) {
		gui.show(!lookGui);
		lookGui = !lookGui;
	}

	if (gui.radioButton(L"mood").hasChanged) {
		Operator::get().clearTarget();
		if (gui.radioButton(L"mood").checked(1)) {
			Dview.show_gui();
		}
		if (gui.radioButton(L"mood").checked(2)) {
			Mview.show_gui();
		}
	}
	if (gui.radioButton(L"mood").checked(1)) {
		Dview.update();
	}
	if (gui.radioButton(L"mood").checked(2)) {
		Mview.update();
	}
	if (gui.radioButton(L"mood").checked(3)) {
		Obj.update();
	}

	Operator::get().update();
}

void Editor::draw() {
	TextureAsset(L"BackGround").draw();
	{
		const Transformer2D transformer(Mat3x2::Translate(-camera.pos + Window::Center()).scale(camera.scale, { 640, 360 }), true);
		Dview.draw(camera.pos);
		Mview.draw(camera.pos);
		Obj.draw(gui.radioButton(L"mood").checked(3));

		Operator::get().draw();

		//雑にグリッド
		int GridSize = 100;
		if (camera.scale < 0.6) GridSize = 250;
		int mouseX = ((int)(Mouse::Pos().x / GridSize) * GridSize);
		for (int y = -10; y < 10; y++) {
			for (int x = -30; x < 30; x++) {
				Rect dot(mouseX + x*GridSize, y*GridSize, GridSize);
				dot.drawFrame(1.0, 1.0, Color(128, 128, 128, 128));
			}
		}
		//y=0の赤線
		Line(Vec2(mouseX - 10000, 0), Vec2(mouseX + 10000, 0)).draw(3.0, Palette::Red);
		//x=0の赤線
		Line(Vec2(0, -10000), Vec2(0, 10000)).draw(3.0, Palette::Red);
		//カメラ位置の赤点
		Circle(camera.pos, 5).draw(Palette::Red);
	}
}
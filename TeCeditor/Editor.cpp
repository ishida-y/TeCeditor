#include "Editor.h"

Editor::Editor() :
	Mview(L"MiddleView", Vec2(0.4, 0.3)),
	Dview(L"DistantView", Vec2(0.2, 0.2)),
	Obj1(L"obj1"),
	Obj2(L"obj2"),
	gui(GUIStyle::Default),
	lookGui(true) {
	//gui設定
	gui.setPos(0, 100);
	gui.setTitle(L"mode");
	gui.add(L"mood", GUIRadioButton::Create({ L"None",L"Dview", L"Mview", L"Obj1" , L"Obj2" }, 0, true));
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
		Obj1.update();
	}
	if (gui.radioButton(L"mood").checked(4)) {
		Obj2.update();
	}

	Operator::get().update();
}

void Editor::draw() {
	TextureAsset(L"BackGround").draw();
	{
		const Transformer2D transformer(Mat3x2::Translate(-camera.pos + Window::Center()).scale(camera.scale, { 640, 360 }), true);
		Dview.draw(camera.pos);
		Mview.draw(camera.pos);
		Obj1.draw(gui.radioButton(L"mood").checked(3));
		Obj2.draw(gui.radioButton(L"mood").checked(4));

		Operator::get().draw();

		//グリッド
		if (lookGui) {
			int GridSize = 100;
			if (camera.scale < 0.6) GridSize = 250;
			int mouseX = ((int)(camera.pos.x / GridSize) * GridSize);
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
}

Editor::~Editor() {
	CSVWriter writer(L"sample.csv");
	writer.write(L"type");
	writer.write(L"name");
	writer.write(L"pos");
	writer.write(L"rot");
	writer.write(L"scale");
	writer.write(L"alpha");

	Dview.write_csv(writer);
	Mview.write_csv(writer);
	Obj1.write_csv(writer);
	Obj2.write_csv(writer);
}
#include "Object.h"
/*
TODO:ägëÂèkè¨èàóù
*/
Object::Object(String _name) :
	name(_name),
	isDead(false),
	rot(0.0),
	scale(1.0, 1.0),
	alpha(255)/*,
	gui(GUIStyle::Default)*/ {

	//ç¿ïWà íu
	pos = Mouse::Pos();
	range = RectF(pos - TextureAsset(name).size, TextureAsset(name).size);

//	//guiê›íË
//	gui.setPos(1280, 0);
//	gui.setTitle(name);
//
//	gui.addln(L"txt_pos", GUIText::Create(L"", 50));
//
//	gui.add(L"txt_rot", GUIText::Create(L"", 50));
//	gui.addln(L"rot", GUISlider::Create(0.0, 100.0, 0.0, 200));
//
//	/*
//	gui.add(L"txt_scaleX", GUIText::Create(L"", 100));
//	gui.addln(L"scaleX", GUISlider::Create(0.0, 300.0, 100.0, 200));
//
//	gui.add(L"txt_scaleY", GUIText::Create(L"", 100));
//	gui.addln(L"scaleY", GUISlider::Create(0.0, 300.0, 100.0, 200));
//*/
//	gui.add(L"txt_alpha", GUIText::Create(L"", 100));
//	gui.addln(L"alpha", GUISlider::Create(0.0, 255.0, 255.0, 200));
//
//	gui.addln(L"Delete", GUIButton::Create(L"Delete"));
//
//	gui.show(false);
}

void Object::draw() {
	TextureAsset(name).scale(scale).rotate(rot).draw(pos - TextureAsset(name).size / 2.0, Color(255, 255, 255, alpha));
	Circle(pos, 10).draw();
}

void Object::edit_update(const GUI& gui) {
	//çÌèú
	if (gui.button(L"Delete").pushed) {
		isDead = true;
	}

	//à⁄ìÆ
	if (Input::MouseL.pressed &&
		range.scaled(scale).rotated(rot).mouseOver) {
		pos += Mouse::Delta();
		range.moveBy(Mouse::Delta());
	}

	//âÒì]
	rot = gui.slider(L"rot").value / 100.0 * 2.0 * Math::Pi;

	/*ägëÂ
	scale.x = (int)(gui.slider(L"scaleX").value / 10.0) / 10.0;
	scale.y = (int)(gui.slider(L"scaleY").value / 10.0) / 10.0;
	*/

	//ÉAÉãÉtÉ@
	alpha = gui.slider(L"alpha").value;
}

void Object::edit_draw() {
	range.scaled(scale).rotated(rot).drawFrame(5);
}

void Object::singleGui_draw(const GUI& gui) {
	gui.text(L"txt_pos").text = Format(L"pos: ", pos);
	gui.text(L"txt_rot").text = Format(L"rot: ", rot / Math::Pi * 180);
	gui.text(L"txt_scaleX").text = Format(L"scaleX: ", scale.x);
	gui.text(L"txt_scaleY").text = Format(L"scaleY: ", scale.y);
	gui.text(L"txt_alpha").text = Format(L"alpha: ", alpha);
}

void Object::set_singleGui(GUI& gui) {
	gui.setTitle(name);
	gui.slider(L"rot").setSliderPosition(rot * 100.0 / Math::Pi);
	gui.slider(L"alpha").setSliderPosition(alpha);
}

void Object::move_pos(Vec2 delta) {
	pos += delta;
	range.moveBy(delta);
}

bool Object::range_mouseOver() {
	return range.scaled(scale).rotated(rot).mouseOver;
}


Vec2 Object::get_pos() {
	return pos;
}
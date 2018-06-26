#include "Object.h"
/*
TODO:ägëÂèkè¨èàóù
*/
Object::Object(String _name, Vec2 _pos, double _rot, Vec2 _scale, int _alpha) :
	name(_name),
	pos(_pos),
	isDead(false),
	rot(_rot),
	scale(_scale),
	alpha(_alpha) {

	//ç¿ïWà íu
	range = RectF(pos - TextureAsset(name).size, TextureAsset(name).size);
}

void Object::draw() {
	TextureAsset(name).scale(scale).rotate(rot).draw(pos - TextureAsset(name).size / 2.0, Color(255, 255, 255, alpha));
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
	if (range.area() != 0) {
		Circle(pos, 5).draw();
	}
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


void Object::write_csv(CSVWriter& writer) {
	writer.write(name);
	writer.write(pos);
	writer.write(rot);
	writer.write(scale);
	writer.write(alpha);
}
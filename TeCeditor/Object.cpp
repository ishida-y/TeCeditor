#include "Object.h"

Object::Object(String _type, int _id) :
	type(_type),
	id(_id),
	hasPhysics(false),
	isDead(false),
	rot(0.0),
	scale(1.0, 1.0),
	alpha(255),
	asset_name(_type + ToString(_id)),
	gui(GUIStyle::Default){
	pos = Mouse::Pos() - TextureAsset(asset_name).size;
	range = RectF(pos, TextureAsset(asset_name).size);
	pos = Mouse::Pos();

	//gui設定
	gui.setPos(1280, 0);
	gui.setTitle(asset_name);

	gui.addln(L"txt_pos", GUIText::Create(L"", 50));

	gui.add(L"txt_rot", GUIText::Create(L"", 50));
	gui.addln(L"rot", GUISlider::Create(0.0, 100.0, 0.0, 200));

	gui.add(L"txt_scaleX", GUIText::Create(L"", 100));
	gui.addln(L"scaleX", GUISlider::Create(0.0, 300.0, 100.0, 200));

	gui.add(L"txt_scaleY", GUIText::Create(L"", 100));
	gui.addln(L"scaleY", GUISlider::Create(0.0, 300.0, 100.0, 200));

	gui.add(L"txt_alpha", GUIText::Create(L"", 100));
	gui.addln(L"alpha", GUISlider::Create(0.0, 255.0, 255.0, 200));

	gui.addln(L"Physics", GUIToggleSwitch::Create(L"非物理", L"物理", hasPhysics));

	gui.addln(L"Delete", GUIButton::Create(L"Delete"));

	gui.show(false);
}

void Object::draw() {
	TextureAsset(asset_name).scale(scale).rotate(rot).draw(pos - TextureAsset(asset_name).size / 2.0, Color(255, 255, 255, alpha));
	Circle(pos, 10).draw();
}

void Object::edit_update() {
	//削除
	if (gui.button(L"Delete").pushed) {
		isDead = true;
	}

	//移動
	if (Input::MouseL.pressed && range.scaled(scale).rotated(rot).mouseOver) {
		pos += Mouse::Delta();
		range.moveBy(Mouse::Delta());
	}

	//回転
	rot = gui.slider(L"rot").value / 100.0 * 2 * Math::Pi;

	//拡大
	scale.x = gui.slider(L"scaleX").value / 100.0;
	scale.y = gui.slider(L"scaleY").value / 100.0;

	//アルファ
	alpha = gui.slider(L"alpha").value;

	//物理
	hasPhysics = gui.toggleSwitch(L"Physics").isRight;

}

void Object::edit_draw() {
	range.scaled(scale).rotated(rot).drawFrame(5);
	gui.text(L"txt_pos").text = Format(L"pos: ", pos);
	gui.text(L"txt_rot").text = Format(L"rot: ", rot / Math::Pi * 180);
	gui.text(L"txt_scaleX").text = Format(L"scaleX: ", scale.x);
	gui.text(L"txt_scaleY").text = Format(L"scaleY: ", scale.y);
	gui.text(L"txt_alpha").text = Format(L"alpha: ", alpha);
}



ObjectManager::ObjectManager(String _type) :
	type(_type),
	selected_obj(-1),
	select_id(0) {
	bool success = true;
	for (id_num = 0; id_num < 10; id_num++) {
		TextureAsset::Register(type + ToString(id_num), L"Data/" + type + ToString(id_num) + L".png");
		success = TextureAsset::Preload(type + ToString(id_num));
		if (!success) {
			break;
		}
	}
}

void ObjectManager::update() {
	//選択する、しない
	int select_obj = selected_obj;
	if (Input::MouseR.clicked) {
		select_obj++;
		int i;
		for (i = 0; i < objs.size(); select_obj++, i++) {
			if (select_obj == objs.size()) {
				select_obj = 0;
			}
			if (objs[select_obj]->range.scaled(objs[select_obj]->scale).rotated(objs[select_obj]->rot).mouseOver) {
				break;
			}
		}
		if (i == objs.size()) {
			select_obj = -1;
		}
	}

	if (selected_obj != select_obj) {
		if(select_obj != -1)objs[select_obj]->gui.show(true);
		if (selected_obj != -1)objs[selected_obj]->gui.show(false);
	}

	selected_obj = select_obj;

	//選択されてないとき
	if (selected_obj == -1) {
		//種類変更
		if (!Input::MouseM.pressed) {
			if (Mouse::Wheel() > 0) {
				select_id++;
				if (select_id >= id_num) {
					select_id = 0;
				}
			}
			else if (Mouse::Wheel() < 0) {
				select_id--;
				if (select_id < 0) {
					select_id = id_num - 1;
				}
			}
		}

		//obj追加(物理なし)
		if (Input::MouseL.clicked) {
			objs.emplace_back(std::make_shared<Object>(type, select_id));
		}
	}

	//選択されているとき
	else {
		objs[selected_obj]->edit_update();
	}

	//削除
	if (selected_obj != -1 && objs[selected_obj]->isDead) {
		selected_obj = -1;
		auto rmvIter = std::remove_if(objs.begin(), objs.end(), [](const std::shared_ptr<Object>& p) {
			return p->isDead;
		});
		objs.erase(rmvIter, objs.end());
	}
}

void ObjectManager::draw() {
	for (int i = 0; i < objs.size(); i++) {
		objs[i]->draw();
	}
	if (selected_obj == -1) {
		Vec2 pos = Mouse::Pos() - TextureAsset(type + ToString(select_id)).size / 2.0;
		TextureAsset(type + ToString(select_id)).draw(pos, Color(255, 255, 255, 128));
	}
	else {
		objs[selected_obj]->edit_draw();
	}
}
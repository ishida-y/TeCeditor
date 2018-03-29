#include "Object.h"

Object::Object(String _type, bool _physics) :
	type(_type),
	physics(_physics),
	isDead(false),
	rot(0.0),
	scale(1.0, 1.0) {
	pos = Mouse::Pos() - TextureAsset(type).size;
	range = RectF(pos, TextureAsset(type).size);
	pos = Mouse::Pos();
}

void Object::draw() {
	TextureAsset(type).scale(scale).rotate(rot).draw(pos - TextureAsset(type).size / 2.0);
	Circle(pos, 10).draw();
}

void Object::edit_update() {
	//削除
	if (Input::KeyBackspace.clicked || Input::KeyDelete.clicked) {
		isDead = true;
	}

	//移動
	if (Input::MouseL.pressed) {
		pos += Mouse::Delta();
		range.moveBy(Mouse::Delta());
	}

	//回転
	if (!Input::MouseM.pressed) {
		if (Mouse::Wheel() > 0) {
			rot += 15.0 / 180.0 * Math::Pi;
		}
		if (Mouse::Wheel() < 0) {
			rot -= 15.0 / 180.0 * Math::Pi;
		}
	}

	//拡大
	if (Input::KeyUp.clicked) {
		scale.y -= 0.1;
	}
	if (Input::KeyDown.clicked) {
		scale.y += 0.1;
	}
	if (Input::KeyRight.clicked) {
		scale.x += 0.1;
	}
	if (Input::KeyLeft.clicked) {
		scale.x -= 0.1;
	}

}

void Object::edit_draw() {
	range.scaled(scale).rotated(rot).drawFrame(5);
	Print(L"ObjPos:");
	Println(pos);
}



ObjectManager::ObjectManager() :
	select_obj(-1),
	select_type(0) {
	bool success = true;
	for (type_num = 0; type_num < 10; type_num++) {
		TextureAsset::Register(L"obj" + ToString(type_num), L"Data/obj" + ToString(type_num) + L".png");
		success = TextureAsset::Preload(L"obj" + ToString(type_num));
		if (!success) {
			break;
		}
	}
}

void ObjectManager::update() {
	//選択する、しない
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

	Print(L"select_obj:");
	Println(select_obj);

	//選択されてないとき
	if (select_obj == -1) {
		//種類変更
		if (!Input::MouseM.pressed) {
			if (Mouse::Wheel() > 0) {
				select_type++;
				if (select_type >= type_num) {
					select_type = 0;
				}
			}
			else if (Mouse::Wheel() < 0) {
				select_type--;
				if (select_type < 0) {
					select_type = type_num - 1;
				}
			}
		}

		Print(L"select_type:");
		Println(select_type);

		//obj追加(物理なし)
		if (Input::MouseL.clicked) {
			objs.emplace_back(std::make_shared<Object>(L"obj" + ToString(select_type), false));
		}
	}

	//選択されているとき
	else {
		objs[select_obj]->edit_update();
	}

	//削除
	if (select_obj != -1 && objs[select_obj]->isDead) {
		select_obj = -1;
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
	if (select_obj == -1) {
		Vec2 pos = Mouse::Pos() - TextureAsset(L"obj" + ToString(select_type)).size / 2.0;
		TextureAsset(L"obj" + ToString(select_type)).draw(pos, Color(255, 255, 255, 128));
	}
	else {
		objs[select_obj]->edit_draw();
	}
}
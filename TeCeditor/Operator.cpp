#include"Operator.h"

Operator::Operator() :
	multiGui(GUIStyle::Default),
	singleGui(GUIStyle::Default) {

	singleGui.setPos(1280, 0);
	singleGui.setTitle(L"Single");
	singleGui.addln(L"txt_pos", GUIText::Create(L"", 50));
	singleGui.add(L"txt_rot", GUIText::Create(L"", 100));
	singleGui.addln(L"rot", GUISlider::Create(0.0, 100.0, 0.0, 200));
	/*
	gui.add(L"txt_scaleX", GUIText::Create(L"", 100));
	gui.addln(L"scaleX", GUISlider::Create(0.0, 300.0, 100.0, 200));
	gui.add(L"txt_scaleY", GUIText::Create(L"", 100));
	gui.addln(L"scaleY", GUISlider::Create(0.0, 300.0, 100.0, 200));
	*/
	singleGui.add(L"txt_alpha", GUIText::Create(L"", 100));
	singleGui.addln(L"alpha", GUISlider::Create(0.0, 255.0, 255.0, 200));
	singleGui.addln(L"Delete", GUIButton::Create(L"Delete"));
	singleGui.show(false);

	multiGui.setPos(1280, 0);
	multiGui.setTitle(L"Multi");
	multiGui.addln(L"size", GUIText::Create(L"", 50));
	multiGui.addln(L"Delete", GUIButton::Create(L"Delete"));
	multiGui.show(false);
}

void Operator::addTarget(std::shared_ptr<Object> _tar) {
	target.emplace_back(_tar);

	//重複チェック
	std::sort(target.begin(), target.end());
	target.erase(std::unique(target.begin(), target.end()), target.end());

	if (target.size() > 1) {
		singleGui.hide();
		multiGui.show();
	}
	else if (target.size() == 1) {
		multiGui.hide();
		//singleGui設定
		target.front()->set_singleGui(singleGui);
		singleGui.show();
	}
	else {
		multiGui.hide();
	}
}

void Operator::changeTarget(std::shared_ptr<Object> _tar) {
	clearTarget();

	addTarget(_tar);
}

void Operator::clearTarget() {
	multiGui.hide();
	singleGui.hide();
	target.clear();
	//std::vector<std::shared_ptr<Object>>().swap(target);
}

void Operator::update() {
	//選択が1つの時
	if (target.size() == 1) {
		target[0]->edit_update(singleGui);
	}

	//選択が複数の時
	else if (target.size() > 1) {
		static Vec2 mouseDelta;
		mouseDelta = Vec2(0, 0);
		for (auto i : target) {
			if (Input::MouseL.pressed && i->range_mouseOver()) {
				mouseDelta = Mouse::Delta();
				break;
			}
		}
		for (auto i : target) {
			i->move_pos(mouseDelta);
			if (multiGui.button(L"Delete").pushed) {
				i->isDead = true;
			}
		}
	}

	//削除
	auto rmvIter = std::remove_if(target.begin(), target.end(), [](const std::shared_ptr<Object>& a) {
		return a->isDead;
	});
	target.erase(rmvIter, target.end());

	if (target.size() == 0) {
		singleGui.hide();
		multiGui.hide();
	}
}

void Operator::draw() {
	for (auto i : target) {
		i->edit_draw();
	}
	if (target.size() == 1) {
		target.front()->singleGui_draw(singleGui);
	}
	else if (target.size() > 1) {
		multiGui.text(L"size").text = Format(L"size: ", target.size());
	}
}

int Operator::getTergetSize() {
	return target.size();
}
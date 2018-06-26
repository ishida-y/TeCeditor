#pragma once
#include <Siv3D.hpp>
#include "Operator.h"
#include"BackGround.h"

class BackGroundManager {
public:
	BackGroundManager(String _type, Vec2 _moveRate);
	void update();
	void draw(Vec2 camera);
	void show_gui();
	void write_csv(CSVWriter& writer);
private:
	String type;
	Vec2 moveRate;
	std::vector<String>::iterator use;
	std::vector<String> names;
	std::shared_ptr<BackGround> obj;
	void change_obj();
};
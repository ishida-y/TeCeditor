#pragma once
#include<Siv3D.hpp>
#include<vector>

class Object {
public:
	Object(String _type, bool _physics);
	void draw();
	void edit_update();
	void edit_draw();

	Vec2 pos;
	int id;
	bool physics;
	String type;
	RectF range;
	bool isDead;
	double rot;
	Vec2 scale;
};

class ObjectManager {
public:
	ObjectManager();
	void draw();
	void update();

	int select_obj;
	int type_num;
	int select_type;
	std::vector<std::shared_ptr<Object>> objs;
};
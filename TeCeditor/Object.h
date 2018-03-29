#pragma once
#include<Siv3D.hpp>
#include<vector>

class Object {
public:
	Object(String _type,int id);
	void draw();
	void edit_update();
	void edit_draw();

	String type;	//種類
	int id;			//番号
	Vec2 pos;		//位置
	bool hasPhysics;	//物理を持つか
	RectF range;	//範囲
	double rot;		//回転角度
	Vec2 scale;		//拡大縮小
	int alpha;		//アルファ値
	bool isDead;	//死亡フラグ

	String asset_name;
	GUI gui;
};

class ObjectManager {
public:
	ObjectManager(String _type);
	void draw();
	void update();

	String type;
	int selected_obj;
	//std::shared_ptr<Object> select_obj;
	int id_num;
	int select_id;
	std::vector<std::shared_ptr<Object>> objs;
};
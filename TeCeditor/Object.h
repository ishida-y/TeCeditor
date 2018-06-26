#pragma once
#include<Siv3D.hpp>
/*
配置する物体のクラス
*/

class Object {
public:
	Object(String _name, Vec2 _pos, double _rot = 0.0, Vec2 _scale = Vec2(1.0, 1.0), int _alpha = 255);
	virtual ~Object() {
	}
	void draw();
	virtual void edit_update(const GUI& gui);
	void edit_draw();
	void singleGui_draw(const GUI& gui);
	void set_singleGui(GUI& gui);
	void move_pos(Vec2 delta);
	bool range_mouseOver();
	Vec2 get_pos();
	void write_csv(CSVWriter& writer);
	bool isDead;	//死亡フラグ

protected:
	Vec2 pos;		//位置
	const String name;	//名前
	double rot;		//回転角度
	Vec2 scale;		//拡大縮小
	int alpha;		//アルファ値
	RectF range;	//範囲
};

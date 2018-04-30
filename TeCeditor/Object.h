#pragma once
#include<Siv3D.hpp>
/*
配置する物体のクラス
*/

class Object {
public:
	Object(String _name);
	virtual ~Object() {
	}
	void draw();		//描画
	virtual void edit_update(const GUI& gui);	//編集処理
	void edit_draw();	//編集描画
	void singleGui_draw(const GUI& gui);
	void set_singleGui(GUI& gui);
	void move_pos(Vec2 delta);
	bool range_mouseOver();
	Vec2 get_pos();
	bool isDead;	//死亡フラグ
protected:
	Vec2 pos;		//位置
	const String name;	//名前
	RectF range;	//範囲
	double rot;		//回転角度
	Vec2 scale;		//拡大縮小
	int alpha;		//アルファ値
};

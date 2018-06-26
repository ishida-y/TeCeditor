#pragma once
#include<Siv3D.hpp>
/*
�z�u���镨�̂̃N���X
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
	bool isDead;	//���S�t���O

protected:
	Vec2 pos;		//�ʒu
	const String name;	//���O
	double rot;		//��]�p�x
	Vec2 scale;		//�g��k��
	int alpha;		//�A���t�@�l
	RectF range;	//�͈�
};

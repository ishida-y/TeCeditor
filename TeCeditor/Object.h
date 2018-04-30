#pragma once
#include<Siv3D.hpp>
/*
�z�u���镨�̂̃N���X
*/

class Object {
public:
	Object(String _name);
	virtual ~Object() {
	}
	void draw();		//�`��
	virtual void edit_update(const GUI& gui);	//�ҏW����
	void edit_draw();	//�ҏW�`��
	void singleGui_draw(const GUI& gui);
	void set_singleGui(GUI& gui);
	void move_pos(Vec2 delta);
	bool range_mouseOver();
	Vec2 get_pos();
	bool isDead;	//���S�t���O
protected:
	Vec2 pos;		//�ʒu
	const String name;	//���O
	RectF range;	//�͈�
	double rot;		//��]�p�x
	Vec2 scale;		//�g��k��
	int alpha;		//�A���t�@�l
};

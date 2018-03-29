#pragma once
#include<Siv3D.hpp>
#include<vector>

class Object {
public:
	Object(String _type,int id);
	void draw();
	void edit_update();
	void edit_draw();

	String type;	//���
	int id;			//�ԍ�
	Vec2 pos;		//�ʒu
	bool hasPhysics;	//����������
	RectF range;	//�͈�
	double rot;		//��]�p�x
	Vec2 scale;		//�g��k��
	int alpha;		//�A���t�@�l
	bool isDead;	//���S�t���O

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
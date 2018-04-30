#pragma once
#include <Siv3D.hpp>
#include"Object.h"
/*
ループ背景用のクラス
Objectクラスから派生
*/
class BackGround : public  Object{
public:
	BackGround(String _name, Vec2 _moveRate, Vec2 _pos);
	void draw(Vec2 camera);
	void edit_update(const GUI& gui);
private:
	Vec2 moveRate;	//カメラに対する移動割合
};

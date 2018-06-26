#pragma once
#include <Siv3D.hpp>
#include"Object.h"
/*
ループ背景用のクラス
Objectクラスから派生
*/
class BackGround : public  Object{
public:
	BackGround(String _name, Vec2 _moveRate, Vec2 _pos, double _rot = 0.0, Vec2 _scale = Vec2(1.0, 1.0), int _alpha = 255);
	void draw(Vec2 camera);
	void edit_update(const GUI& gui);
private:
	Vec2 moveRate;	//カメラに対する移動割合
};

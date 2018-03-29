#include"MiddleView.h"
#include<Siv3D.hpp>

MiddleView::MiddleView() {
	TextureAsset::Register(L"Mview", L"Data/MiddleView.png");
}

void MiddleView::draw(Vec2 camera) {
	Vec2 temp(Window::Center() - camera);
	double tmp_y = 0.4;//0.2
	double tmp_x = 0.4;
	TextureAsset(L"Mview").draw(Vec2(temp.x * tmp_x, temp.y*tmp_y - 200));
	TextureAsset(L"Mview").draw(Vec2(temp.x * tmp_x + 2560, temp.y*tmp_y - 200));
	TextureAsset(L"Mview").draw(Vec2(temp.x * tmp_x - 2560, temp.y*tmp_y - 200));
	TextureAsset(L"Mview").draw(Vec2(temp.x * tmp_x + 5120, temp.y*tmp_y - 200));
	TextureAsset(L"Mview").draw(Vec2(temp.x * tmp_x - 5120, temp.y*tmp_y - 200));

}
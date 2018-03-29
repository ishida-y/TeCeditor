#include"DistantView.h"
#include<Siv3D.hpp>

DistantView::DistantView() {
	TextureAsset::Register(L"Dview", L"Data/DistantView.png");
}

void DistantView::draw(Vec2 camera) {
	Vec2 temp(Window::Center() - camera);
	double tmp = 0.8;//0.4
	double tmp2 = 0.8;
	TextureAsset(L"Dview").draw(Vec2(temp.x * tmp2, temp.y * tmp - 200));
	TextureAsset(L"Dview").draw(Vec2(temp.x * tmp2 + 1280, temp.y * tmp - 200));
	TextureAsset(L"Dview").draw(Vec2(temp.x * tmp2 - 1280, temp.y * tmp - 200));
	TextureAsset(L"Dview").draw(Vec2(temp.x * tmp2 + 2560, temp.y * tmp - 200));
	TextureAsset(L"Dview").draw(Vec2(temp.x * tmp2 - 2560, temp.y * tmp - 200));

}
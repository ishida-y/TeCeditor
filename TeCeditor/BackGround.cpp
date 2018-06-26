#include "BackGround.h"

BackGround::BackGround(String _name, Vec2 _moveRate, Vec2 _pos, double _rot, Vec2 _scale, int _alpha) :
	Object(_name, _pos, _rot, _scale, _alpha),
	moveRate(_moveRate) {
	//�͈͔���͖���
	range = RectF(Vec2(0, 0), Vec2(0, 0));
}


void BackGround::draw(Vec2 camera) {
	//���[�v�`�揈��
	Vec2 tmp = Vec2(camera.x * (1 - moveRate.x), camera.y *(1 - moveRate.y));//�����̍�
	double x = pos.x + tmp.x;//��ԍ���x�ʒu
	const static int loop = 4;//����
	while (camera.x - x > TextureAsset(name).width * loop / 2.0) {
		x += TextureAsset(name).width;
	}
	for (int i = 0; i < loop; i++) {
		TextureAsset(name).draw(Vec2(x, tmp.y + pos.y), Color(255, 255, 255, alpha));
		x += TextureAsset(name).width;
	}
}

void BackGround::edit_update(const GUI& gui) {
	//�폜
	if (gui.button(L"Delete").pushed) {
		isDead = true;
	}

	//�ړ�
	if (Input::MouseL.pressed) {
		pos += Mouse::Delta();
		range.moveBy(Mouse::Delta());
	}

	/*�g��
	scale.x = (int)(gui.slider(L"scaleX").value / 10.0) / 10.0;
	scale.y = (int)(gui.slider(L"scaleY").value / 10.0) / 10.0;
	*/

	//�A���t�@
	alpha = gui.slider(L"alpha").value;
}
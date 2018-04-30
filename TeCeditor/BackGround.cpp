#include "BackGround.h"

BackGround::BackGround(String _name, Vec2 _moveRate, Vec2 _pos) :
	Object(_name),
	moveRate(_moveRate) {
	////gui�\���ݒ�
	//gui.slider(L"rot").enabled = false;
	////gui.slider(L"scaleX").enabled = false;
	////gui.slider(L"scaleY").enabled = false;
	//gui.slider(L"alpha").enabled = false;
	//gui.button(L"Delete").enabled = false;
	pos = _pos;
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
	if (Input::MouseL.pressed &&
		range.scaled(scale).rotated(rot).mouseOver) {
		pos += Mouse::Delta();
		range.moveBy(Mouse::Delta());
	}

	//��]
	//rot = gui.slider(L"rot").value / 100.0 * 2.0 * Math::Pi;

	/*�g��
	scale.x = (int)(gui.slider(L"scaleX").value / 10.0) / 10.0;
	scale.y = (int)(gui.slider(L"scaleY").value / 10.0) / 10.0;
	*/

	//�A���t�@
	alpha = gui.slider(L"alpha").value;
}
#pragma once
#include "character.h"
#ifndef player_
#define player_

class Player : public Character {
private:
	bool jump_bool;	// ���� ���� ������ �Ǻ�
	float jump_power;

public:
	Player() {
		jump_bool = false;
		jump_power = 0.0;

		x = 0.0; y = 0.0; z = -10.0;	// ���� �������� �������� �÷��̾� ���� ��ǥ �޾ƿ���  
		x_width = 0.4; height = 1.0, z_width = 0.2; // �浹ó���� ���, ���� ������ �� ã�� ���� �ʿ�
		x_angle = 0.0; y_angle = 0.0;
		speed = 1.0;	// ������ ������ ���� �ʿ�
		shot_bool = false;	// ���� �� �� �ִ� ��������
	};
	~Player() = default;

	void Move_Right();
	void Move_Left();
	void Move_Front();
	void Move_Back();

	void Rotate(int mouse_x, int mouse_y, float time);	// ���콺 ��ǥ�� ���� ȸ��.  ���� ���콺 ��ǥ - ���� ���콺 ��ǥ�� ���� �޾ƿ´� 
};

#endif
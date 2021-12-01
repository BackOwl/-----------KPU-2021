#pragma once
#include "gun.h"
#ifndef character_
#define character_

class Character {
protected:
	float x, y, z;
	float x_width, height, z_width; // �浹ó���� ���
	float speed;
	float x_angle, y_angle;	// ���� ���� �ִ� ���� ����� �˱� ���� ĳ���� ���� ǥ��, �Ѿ� �߻�. ���ΰ��� ���� �ִ� ��� ���� ����

	Gun* gun;
public:
	Character() = default;
	~Character() = default;

	void GetPos(float* input_x, float* input_y, float* input_z);
	float GetXangle();
	float GetYangle();
};

#endif
#pragma once
#include "gun.h"
#include "bullet.h"
#ifndef character_
#define character_

class Character {
protected:
	float x, y, z;
	float x_width, height, z_width; // �浹ó���� ���
	float speed;
	float x_angle, y_angle;	// ���� ���� �ִ� ���� ����� �˱� ���� ĳ���� ���� ǥ��, �Ѿ� �߻�. ���ΰ��� ���� �ִ� ��� ���� ����
public:
	Gun gun;

	Character() = default;
	~Character() = default;

	void Move_Right(float time);
	void Move_Left(float time);
	void Move_Front(float time);
	void Move_Back(float time);

	void GetPos(float* input_x, float* input_y, float* input_z);
	float GetXangle();
	float GetYangle();
	bool collide_bullet(std::vector<Bullet>* v);	// �浹 ó��
};

#endif
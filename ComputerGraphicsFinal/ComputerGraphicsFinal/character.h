#pragma once

class Character {
protected:
	float x, y, z;
	float x_width, height, z_width; // �浹ó���� ���
	float speed;
	float x_angle, y_angle;	// ���� ���� �ִ� ���� ����� �˱� ���� ĳ���� ���� ǥ��, �Ѿ� �߻�. ���ΰ��� ���� �ִ� ��� ���� ����
	bool shot_bool;	// ���� �� �� �ִ� ��������
public:
	Character() {};
	~Character() {};

	void GetPos(float* input_x, float* input_y, float* input_z);
	float GetXangle();
	float GetYangle();
};
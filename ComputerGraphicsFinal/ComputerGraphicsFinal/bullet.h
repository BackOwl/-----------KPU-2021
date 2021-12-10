#pragma once
#include <gl/glm/gtc/matrix_transform.hpp>
#include <gl/glew.h>
#include <gl/glm/ext.hpp>
#include <vector>
#ifndef bullet_
#define bullet_

class Bullet {
protected:
	float x, y, z;
	float start_x, start_y, start_z;
	float x_width, height, z_width; // �浹ó���� ���
	float speed;
	float len;
	float x_angle, y_angle;	// ���� ���� �ִ� ���� ����� �˱� ���� ĳ���� ���� ǥ��, �Ѿ� �߻�. ���ΰ��� ���� �ִ� ��� ���� ����
	bool character;	// True�� player�� �� ��. False�� ���� ���
public:
	Bullet(float s_x, float s_y, float s_z, float s_x_angle, float s_y_angle, bool in_character) {
		x = s_x;
		start_x = s_x;
		y = s_y;
		start_y = s_y;
		z = s_z;
		start_z = s_z;
		x_angle = s_x_angle;
		y_angle = s_y_angle;
		len = 0.0;
		x_width = height = z_width = 0.01;
		character = in_character;

		speed = 30.0;
	}
	~Bullet() = default;

	bool len_check();

	void Update(float time);

	void Draw(unsigned int modelLocation, unsigned int colorLocation, int numTriangle);

	void GetPos(float* input_x, float* input_y, float* input_z);
};


#endif


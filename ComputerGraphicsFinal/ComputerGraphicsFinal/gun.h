#pragma once
#include <gl/glm/gtc/matrix_transform.hpp>
#include <gl/glew.h>
#include <gl/glm/ext.hpp>
#ifndef gun_
#define gun_

class Gun {
private:
	bool shot_bool;	
	float shot_power;
	//float shot_timer;
	float shot_angle;
	float x_angle, y_angle;
	float x, y, z;
	float size;

public:
	Gun() = default;
	Gun(float in_x, float in_y, float in_z, float in_x_angle, float in_y_angle) {
		shot_bool = true;
		shot_power = 0.0;
		//shot_timer = 0.0;
		shot_angle = 0.0;

		x = in_x; y = in_y; z = in_z;
		size = 1.0;	// ���� ����
		x_angle = in_x_angle;
		y_angle = in_y_angle;
	};
	~Gun() = default;
	
	void Set(float in_x, float in_y, float in_z, float in_x_angle, float in_y_angle);	// ĳ���� ��ü ��ġ + ���� ������Ʈ

	void Update(float time);	// �� �ݵ� ���� update ������

	void Draw(unsigned int modelLocation, unsigned int colorLocation, int numTriangle);

	bool Shot();	// �� �߻� �������� üũ & �� �ݵ� ����.
	
	void Pos();


};

#endif
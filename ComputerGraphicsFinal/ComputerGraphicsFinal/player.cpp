#include "player.h"


void Player::Move_Right() 
{

}

void Player::Move_Left()
{

}
void Player::Move_Front()
{

}
void Player::Move_Back() 
{

}

void Player::Rotate(int mouse_x, int mouse_y)	// ���콺 ��ǥ�� ���� ȸ��.  ���� ���콺 ��ǥ - ���� ���콺 ��ǥ�� ���� �޾ƿ´� 
{
	x_angle += (float)mouse_x / 5.0;
	y_angle += (float)mouse_y / 10.0;
	if (y_angle < -90.0) {
		y_angle = -90.0;
	}
	if (y_angle > 90.0) {
		y_angle = 90.0;
	}
}
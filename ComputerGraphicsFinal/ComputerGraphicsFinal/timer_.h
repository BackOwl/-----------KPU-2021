#pragma once
#ifndef timer_
#define timer_
#include <windows.h>

class Timer_ {
private:
	bool slow;	//  ��ư�� �� ������ �� (wasd, space) true

	LARGE_INTEGER tSecond;
	LARGE_INTEGER curTime;
	LARGE_INTEGER prevTime;
	float deltaTime;
	float deltaSlowTime;

public:
	Timer_() {
		QueryPerformanceFrequency(&tSecond);    // �ʴ� Ŭ�ϼ� ��������
		QueryPerformanceCounter(&curTime);
		QueryPerformanceCounter(&prevTime);
	};
	~Timer_() = default;
	
	float DeltaTime();	// ȭ�� ȸ�� � ���

	float SlowDeltaTime();	// ĳ���� �̵�, �Ѿ� �̵�, �� �߻� �� �ݵ� � ���

	void  SetTimerFast();

	void Update();

	void Reset();
};

#endif


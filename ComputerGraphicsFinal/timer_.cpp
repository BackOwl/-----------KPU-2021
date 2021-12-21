#include "timer_.h"

float Timer_::DeltaTime()	// ȭ�� ȸ�� � ���
{
	return deltaTime;
}

float  Timer_::SlowDeltaTime()	// ĳ���� �̵�, �Ѿ� �̵�, �� �߻� �� �ݵ� � ���
{
	return deltaSlowTime;
}

void  Timer_::Update()
{
	QueryPerformanceCounter(&curTime);
	deltaTime = (static_cast<double>(curTime.QuadPart) - static_cast<double>(prevTime.QuadPart)) / static_cast<double>(tSecond.QuadPart);
	if (slow) {
		deltaSlowTime = deltaTime / 10.0;
	}
	else {
		deltaSlowTime = deltaTime;
	}

	slow = true;
	QueryPerformanceCounter(&prevTime);
}

void  Timer_::SetTimerFast()
{
	slow = false;
}

void  Timer_::Reset()
{
	QueryPerformanceFrequency(&tSecond);    // �ʴ� Ŭ�ϼ� ��������
	QueryPerformanceCounter(&curTime);
	QueryPerformanceCounter(&prevTime);
}


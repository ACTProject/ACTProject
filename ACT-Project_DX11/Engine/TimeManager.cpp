#include "pch.h"
#include "TimeManager.h"

void TimeManager::Init()
{
	// CPU의 고해상도 타이머의 주파수(초당 카운트 수)를 가져옵니다.
	::QueryPerformanceFrequency(reinterpret_cast<LARGE_INTEGER*>(&_frequency));
	// 현재 CPU 타이머의 값을 가져옵니다.
	::QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&_prevCount));
}

void TimeManager::Update()
{
	// 현재 프레임의 CPU 타이머 값을 가져와 currentCount에 저장합니다.
	uint64 currentCount;
	::QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&currentCount));

	// 이전 프레임과 현재 프레임 사이의 시간(초 단위)을 계산합니다.
	_deltaTime = (currentCount - _prevCount) / static_cast<float>(_frequency);
	_prevCount = currentCount;

	// 1초 동안 처리된 프레임 수 카운트
	_frameCount++;
	// 누적 시간
	_frameTime += _deltaTime;

	// 누적 시간이 1초를 초과하면 FPS를 계산
	if (_frameTime > 1.f)
	{
		// 초당 프레임 수를 계산하여 저장합니다
		_fps = static_cast<uint32>(_frameCount / _frameTime);

		_frameTime = 0.f;
		_frameCount = 0;
	}
}
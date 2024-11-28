#include "pch.h"
#include "TimeManager.h"
#include <thread>

void TimeManager::Init()
{
    // CPU의 고해상도 타이머의 주파수(초당 카운트 수)를 가져옵니다.
    ::QueryPerformanceFrequency(reinterpret_cast<LARGE_INTEGER*>(&_frequency));
    // 현재 CPU 타이머의 값을 가져옵니다.
    ::QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&_prevCount));

    // 목표 프레임 시간 (60 FPS = 1 / 60초)
    _targetFrameTime = 1.0f / 60.f;
}

void TimeManager::Update()
{
    // 현재 프레임의 CPU 타이머 값을 가져와 currentCount에 저장합니다.
    uint64 currentCount;
    ::QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&currentCount));

    // 이전 프레임과 현재 프레임 사이의 시간(초 단위)을 계산합니다.
    _deltaTime = (currentCount - _prevCount) / static_cast<float>(_frequency);

    // 목표 프레임 시간보다 빠를 경우 대기
    while (_deltaTime < _targetFrameTime)
    {
        // 현재 프레임까지 누적 시간 계산
        ::QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&currentCount));
        _deltaTime = (currentCount - _prevCount) / static_cast<float>(_frequency);
    }

    // 프레임이 완료되었으므로 이전 타이머 값을 갱신
    _prevCount = currentCount;

    // FPS 계산
    _frameCount++;
    _frameTime += _deltaTime;

    if (_frameTime >= 1.0f)
    {
        _fps = static_cast<uint32>(_frameCount);
        _frameCount = 0;
        _frameTime = 0.0f;
    }
}


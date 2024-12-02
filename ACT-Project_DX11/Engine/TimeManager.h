#pragma once


class TimeManager
{
	DECLARE_SINGLE(TimeManager);

public:
	void Init();
	void Update();

	uint32 GetFps() { return _fps; }
	float GetDeltaTime() { return _deltaTime; }

private:
	uint64	_frequency = 0;		
	uint64	_prevCount = 0;
	float	_deltaTime = 0.f; // 현재 프레임의 경과 시간

private:
	float	_frameTime = 0.f;
	uint32	_frameCount = 0;
	float	_fps = 0;
	float _targetFrameTime = 0.f;
};


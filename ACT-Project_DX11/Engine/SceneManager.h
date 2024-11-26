#pragma once
#include "Scene.h"

class SceneManager
{
	DECLARE_SINGLE(SceneManager);

public:
	void Awake();		// 다른 오브젝트나 컴포넌트를 참조하기 전에 실행
	void Start();		// 오브젝트 활성화된 이후 초기화 수행
	void FixedUpdate();		// 매 프레임마다 호출
	void Update();		// 매 프레임마다 호출

	void AddScene(const std::string& name, std::shared_ptr<Scene> scene);
	void ChangeScene(const string& name);

	shared_ptr<Scene> GetCurrentScene() { return _currentScene; }
	float GetFixedDeltaTime() { return _fixedDeltaTime; }

private:
	shared_ptr<Scene> _currentScene = make_shared<Scene>();
	unordered_map<string, shared_ptr<Scene>> _scenes;

	const float _fixedDeltaTime = 0.02f; // Fixed timestep (20ms)
	float _accumulatedTime = 0.0f;			// 누적된 시간
	float _deltaTime = 0.0f;				// 현재 프레임의 경과 시간
};


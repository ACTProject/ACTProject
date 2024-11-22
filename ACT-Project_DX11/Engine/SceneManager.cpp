#include "pch.h"
#include "SceneManager.h"

void SceneManager::Awake()
{
	if (_currentScene != nullptr)
	{
		_currentScene->Awake();
	}
}

void SceneManager::Start()
{
	if (_currentScene != nullptr)
	{
		_currentScene->Start();
	}
}

void SceneManager::FixedUpdate()
{
	// 1. 현재 프레임에서 경과한 시간 계산
	_deltaTime = TIME->GetDeltaTime();

	// 2. 경과 시간을 누적
	_accumulatedTime += _deltaTime;

	// 3. 고정된 간격으로 FixedUpdate 호출
	while (_accumulatedTime >= _fixedDeltaTime)
	{
		_currentScene->FixedUpdate();
		_accumulatedTime -= _fixedDeltaTime;
	}
}

void SceneManager::Update()
{
	if (_currentScene == nullptr)
		return;

	_currentScene->Update();
	_currentScene->LateUpdate();

	_currentScene->Render();
}

void SceneManager::AddScene(const std::string& name, std::shared_ptr<Scene> scene)
{
	if (_scenes.find(name) != _scenes.end())
	{
		// 이미 같은 이름의 씬이 있다면 경고 출력
		std::cerr << "Scene \"" << name << "\" already exists!" << std::endl;
		return;
	}

	_scenes[name] = scene;
}

void SceneManager::ChangeScene(const string& name)
{
	auto it = _scenes.find(name);
    if (it == _scenes.end())
    {
        // 해당 이름의 씬이 없는 경우 경고 출력
        std::cerr << "Scene \"" << name << "\" does not exist!" << std::endl;
        return;
    }

    // 현재 씬 변경 및 생명주기 초기화
    _currentScene = it->second;
    _currentScene->Awake();
    _currentScene->Start();
}

#pragma once
#include "Component.h"
class Slider :
	public Component
{
	using Super = Component;

public:
	Slider();
	virtual ~Slider();

	bool Picked(POINT screenPos);

	void Create(Vec2 screenPos, Vec2 size, shared_ptr<class Material> material);
	void AddOnClickedEvent(std::function<void(void)> func);
	void InvokeOnClicked();

private:
	std::function<void(void)> _onClicked;
	RECT _rect;
};

//class Component
//{
//public:
//	Component(ComponentType type);
//	virtual ~Component();
//
//	virtual void Awake() { }
//	virtual void Start() { }
//	virtual void Update() { }
//	virtual void LateUpdate() { }
//	virtual void FixedUpdate() { }
//
//public:
//	ComponentType GetType() { return _type; }
//
//	shared_ptr<GameObject> GetGameObject();
//	shared_ptr<Transform> GetTransform();
//
//private:
//	friend class GameObject;
//	void SetGameObject(shared_ptr<GameObject> gameObject) { _gameObject = gameObject; }
//
//protected:
//	ComponentType _type;
//	weak_ptr<GameObject> _gameObject;
//};

// scene의 업데이트에서 if문으로 false를 하면서 게임옵젝을 돌면서 그게 button이면 invokeonclicked 함수 쓰고 있음.
// MeshRenderer::RenderSingle() 체크

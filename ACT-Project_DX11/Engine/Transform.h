#pragma once
#include "Component.h"

class Transform : public Component
{
	using Super = Component;
public:
	Transform();
	~Transform();

	virtual void Awake() override;
	virtual void Update() override;

	void UpdateTransform();

	static Vec3 ToEulerAngles(Quaternion q);

	// Local
	Vec3 GetLocalScale() { return _localScale; }
	void SetLocalScale(const Vec3& localScale) { _localScale = localScale; UpdateTransform(); }
	Vec3 GetLocalRotation() { return _localRotation; }
	void SetLocalRotation(const Vec3& localRotation) { _localRotation = localRotation; UpdateTransform(); }
	Vec3 GetLocalPosition() { return _localPosition; }
	void SetLocalPosition(const Vec3& localPosition) { _localPosition = localPosition; UpdateTransform(); }

	void SetLocalCenter(const Vec3& localCenter) { _localCenter = localCenter; }

	// World
	Vec3 GetScale() { return _scale; }
	void SetScale(const Vec3& scale);
	Vec3 GetRotation() { return _rotation; }
	void SetRotation(const Vec3& rotation);
	Vec3 GetPosition() { return _position; }
	void SetPosition(const Vec3& position);

	Vec3 GetRight();
	Vec3 GetUp(); 
	Vec3 GetLook();

	Matrix GetWorldMatrix() { return _matWorld; }
	void SetWorldMatrix(Matrix matWorld) { _matWorld = matWorld; }

	// 계층 관계
	bool HasParent() { return _parent != nullptr; }
	
	shared_ptr<Transform> GetParent() { return _parent; }
	void SetParent(shared_ptr<Transform> parent) { _parent = parent; }

	const vector<shared_ptr<Transform>>& GetChildren() { return _children; }
	void AddChild(shared_ptr<Transform> child) { _children.push_back(child); }

private:
	Vec3 _localScale = { 1.f, 1.f, 1.f }; 
	Vec3 _localRotation = { 0.f, 0.f, 0.f };
	Vec3 _localPosition = { 0.f, 0.f, 0.f };
	
	// 오브젝트 로컬 중심좌표 옮기는 변수
	Vec3 _localCenter = { 0.f, 0.f, 0.f };
	//Matrix _matCenter = Matrix::Identity;

	// Cache
	Matrix _matLocal = Matrix::Identity;
	Matrix _matWorld = Matrix::Identity;
	
	Vec3 _scale;
	Vec3 _rotation;
	Vec3 _position;

private:
	shared_ptr<Transform> _parent;
	vector<shared_ptr<Transform>> _children;
};


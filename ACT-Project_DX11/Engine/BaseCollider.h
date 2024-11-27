#pragma once
#include "Component.h"

enum class ColliderType
{
	Sphere,
	AABB,
	OBB,
};

class BaseCollider : public Component
{
public:
	BaseCollider(ColliderType colliderType);
	virtual ~BaseCollider();

	virtual bool Intersects(Ray& ray, OUT float& distance) = 0;
	virtual bool Intersects(shared_ptr<BaseCollider>& other) = 0;

	virtual void RenderCollider(shared_ptr<class Shader> shader) = 0;

	ColliderType GetColliderType() { return _colliderType; }
	void SetOffset(const Vec3& offset) { _offset = offset; }
	Vec3 GetOffset() const { return _offset; }

protected:
	ColliderType _colliderType;
	Vec3 _offset = Vec3(0.0f); // Collider ¡ﬂΩ…¿« offset
};


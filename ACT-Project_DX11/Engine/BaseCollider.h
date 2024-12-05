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
	virtual bool Intersects(const shared_ptr<BaseCollider>& other) = 0;
	virtual bool Intersects(const BoundingBox& box) const = 0;
	virtual void RenderCollider(shared_ptr<InstancingBuffer>& buffer) = 0;
    virtual void AppendVertices(vector<VertexPosData>& vertexData) const = 0;
	virtual bool CalculatePenetraionDepth(shared_ptr<BaseCollider> other, Vec3& penetraionDepth) = 0;

	bool CalculateAABBAABBCollision(const BoundingBox& boxA, const BoundingBox& boxB, Vec3& penetrationDepth);
	bool CalculateAABBSphereCollision(const BoundingBox& box, const BoundingSphere& sphere, Vec3& penetrationDepth);
	bool CalculateSphereSphereCollision(const BoundingSphere& sphereA, const BoundingSphere& sphereB, Vec3& penetrationDepth);

    InstanceID GetInstanceID();

    // AABB와 Sphere를 위한 가상 메서드
    virtual BoundingBox GetBoundingBox() const { return BoundingBox(); }
    virtual BoundingSphere GetBoundingSphere() const { return BoundingSphere(); }

    ColliderType GetColliderType() { return _colliderType; }
	void SetOffset(const Vec3& offset) { _offset = offset; }
	Vec3 GetOffset() const { return _offset; }
	Vec3 GetColliderCenter() { return GetGameObject()->GetTransform()->GetPosition() + _offset; }
	bool IsColliding() const { return _isColliding; }
	void SetColliding(bool isColliding) { _isColliding = isColliding; }

	// 활성화 상태 관리
	bool IsActive() const { return _isActive; }
	void SetActive(bool isActive) { _isActive = isActive; }

protected:
	ColliderType _colliderType;
	Vec3 _offset = Vec3(0.0f); // Collider 중심의 offset

private:
	bool _isColliding = false; // 충돌 상태 추적
	bool _isActive = true; // 기본값: 활성화 상태
};


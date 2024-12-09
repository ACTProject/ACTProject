#include "pch.h"
#include "OBBBoxCollider.h"
#include "SphereCollider.h"
#include "AABBBoxCollider.h"
#include "Camera.h"

OBBBoxCollider::OBBBoxCollider() : BaseCollider(ColliderType::OBB)
{

}

OBBBoxCollider::~OBBBoxCollider()
{

}

void OBBBoxCollider::Update()
{
	//_boundingOrientedBox.Center = GetColliderCenter();
}

bool OBBBoxCollider::Intersects(const Ray& ray, OUT float& distance)
{
	return _boundingOrientedBox.Intersects(ray.position, ray.direction, OUT distance);
}

bool OBBBoxCollider::Intersects(const shared_ptr<BaseCollider>& other)
{
	ColliderType type = other->GetColliderType();

	switch (type)
	{
	case ColliderType::Sphere:
		return _boundingOrientedBox.Intersects(dynamic_pointer_cast<SphereCollider>(other)->GetBoundingSphere());
	case ColliderType::AABB:
		return _boundingOrientedBox.Intersects(dynamic_pointer_cast<AABBBoxCollider>(other)->GetBoundingBox());
	case ColliderType::OBB:
		return _boundingOrientedBox.Intersects(dynamic_pointer_cast<OBBBoxCollider>(other)->GetBoundingBox());
	}

	return false;
}

void OBBBoxCollider::RenderCollider(shared_ptr<class InstancingBuffer>& buffer)
{
    // TODO
}

bool OBBBoxCollider::CalculatePenetraionDepth(shared_ptr<BaseCollider> other, Vec3& penetrationDepth)
{
	// TODO

	return false;
}

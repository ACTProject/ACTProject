#include "pch.h"
#include "BaseCollider.h"
#include "SphereCollider.h"
#include "AABBBoxCollider.h"
#include "MeshRenderer.h"
#include "ModelRenderer.h"
#include "ModelAnimator.h"

BaseCollider::BaseCollider(ColliderType colliderType)
	: Component(ComponentType::Collider), _colliderType(colliderType)
{

}

BaseCollider::~BaseCollider()
{

}

bool BaseCollider::CalculateAABBAABBCollision(const BoundingBox& boxA, const BoundingBox& boxB, Vec3& penetrationDepth)
{
	Vec3 minA = Vec3(boxA.Center.x - boxA.Extents.x,
		boxA.Center.y - boxA.Extents.y,
		boxA.Center.z - boxA.Extents.z);

	Vec3 maxA = Vec3(boxA.Center.x + boxA.Extents.x,
		boxA.Center.y + boxA.Extents.y,
		boxA.Center.z + boxA.Extents.z);

	Vec3 minB = Vec3(boxB.Center.x - boxB.Extents.x,
		boxB.Center.y - boxB.Extents.y,
		boxB.Center.z - boxB.Extents.z);

	Vec3 maxB = Vec3(boxB.Center.x + boxB.Extents.x,
		boxB.Center.y + boxB.Extents.y,
		boxB.Center.z + boxB.Extents.z);

	float dx = min(maxA.x - minB.x, maxB.x - minA.x);
	float dy = min(maxA.y - minB.y, maxB.y - minA.y);
	float dz = min(maxA.z - minB.z, maxB.z - minA.z);

	if (dx > 0 && dy > 0 && dz > 0) // 겹침 발생
	{
		penetrationDepth = Vec3(dx, dy, dz);
		return true;
	}

	penetrationDepth = Vec3(0.f); // 겹침 없음
	return false;
}

bool BaseCollider::CalculateAABBSphereCollision(const BoundingBox& box, const BoundingSphere& sphere, Vec3& penetrationDepth)
{
	// 1. Sphere의 중심을 AABB 범위로 Clamp하여 가장 가까운 점 계산
	Vec3 closestPoint;
	closestPoint.x = max(box.Center.x - box.Extents.x, min(sphere.Center.x, box.Center.x + box.Extents.x));
	closestPoint.y = max(box.Center.y - box.Extents.y, min(sphere.Center.y, box.Center.y + box.Extents.y));
	closestPoint.z = max(box.Center.z - box.Extents.z, min(sphere.Center.z, box.Center.z + box.Extents.z));

	// 2. Sphere의 중심과 AABB 가장 가까운 점 간의 거리 계산
	Vec3 difference = sphere.Center - closestPoint;
	float distanceSquared = difference.LengthSquared(); // 거리의 제곱
	float radiusSquared = sphere.Radius * sphere.Radius; // Sphere 반지름 제곱

	if (distanceSquared < radiusSquared) // 충돌 발생
	{
		// 충돌 깊이 계산
		float distance = sqrt(distanceSquared);
		float penetration = sphere.Radius - distance;

		if (distance > 0) // 중심이 정확히 겹치지 않았을 때 방향 계산
		{
			difference.Normalize();
			penetrationDepth = difference * penetration;
		}
		else
			penetrationDepth = Vec3(0.f);

		return true;
	}

	// 충돌 없음
	penetrationDepth = Vec3(0.f);
	return false;
}

bool BaseCollider::CalculateSphereSphereCollision(const BoundingSphere& sphereA, const BoundingSphere& sphereB, Vec3& penetrationDepth)
{
	Vec3 centerA = sphereA.Center;
	Vec3 centerB = sphereB.Center;

	Vec3 centerNormal = centerB - centerA;
	centerNormal.Normalize();
	float distance = (centerB - centerA).Length();
	float radiusSum = sphereA.Radius + sphereB.Radius;

	if (distance < radiusSum) // 겹침 발생
	{
		penetrationDepth = (radiusSum - distance) * centerNormal;
		return true;
	}

	penetrationDepth = Vec3(0.f); // 겹침 없음
	return false;
}

InstanceID BaseCollider::GetInstanceID()
{
    auto go = GetGameObject();
    if (go->GetMeshRenderer() != nullptr)
        return go->GetMeshRenderer()->GetInstanceID();
    if (go->GetModelRenderer() != nullptr)
        return go->GetModelRenderer()->GetInstanceID();
    if (go->GetModelAnimator() != nullptr)
        return go->GetModelAnimator()->GetInstanceID();

    return make_pair(DEFAULT_MESH_ID, DEFAULT_MATERIAL_ID);
}
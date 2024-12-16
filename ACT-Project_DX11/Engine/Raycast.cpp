#include "pch.h"
#include "Raycast.h"
#include "BaseCollider.h"

Raycast::Raycast() : Super(ComponentType::Raycast)
{

}

Raycast::~Raycast()
{

}

bool Raycast::CheckRaycast(Ray& ray, float maxDistance, RaycastHit& hit)
{
    //// Octree를 사용하여 충돌 가능한 객체 검색
    //std::vector<std::shared_ptr<BaseCollider>> potentialColliders = OCTREE->QueryColliders(ray);

    //bool isHit = false;
    //float closestDistance = maxDistance;

    //for (const auto& collider : potentialColliders)
    //{
    //    float distance;
    //    if (collider->Intersects(ray, distance) && distance < closestDistance)
    //    {
    //        closestDistance = distance;
    //        hit.hitPoint = ray.position + ray.direction * distance;
    //        hit.hitCollider = collider;
    //        hit.distance = distance;
    //        isHit = true;
    //    }
    //}

    return false;
}
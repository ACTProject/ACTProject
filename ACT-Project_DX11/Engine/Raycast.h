#pragma once
#include "Component.h"

struct RaycastHit
{
    Vec3 hitPoint;
    std::shared_ptr<BaseCollider> hitCollider;
    float distance;
};

class Raycast : public Component
{
    using Super = Component;
public:
    Raycast();
    virtual ~Raycast();

    bool CheckRaycast(Ray& ray, float maxDistance, RaycastHit& hit);

};


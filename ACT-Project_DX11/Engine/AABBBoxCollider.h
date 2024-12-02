#pragma once
#include "BaseCollider.h"


class AABBBoxCollider : public BaseCollider
{
public:
	AABBBoxCollider();
	virtual ~AABBBoxCollider();

	virtual void Update() override;
	virtual bool Intersects(Ray& ray, OUT float& distance) override;
	virtual bool Intersects(shared_ptr<BaseCollider>& other) override;
	virtual void RenderCollider(shared_ptr<class Shader> shader) override;
	virtual bool CalculatePenetraionDepth(shared_ptr<BaseCollider> other, Vec3& penetraionDepth) override;

	BoundingBox& GetBoundingBox() { return _boundingBox; }

private:
	BoundingBox _boundingBox;
};

#pragma once
#include "BaseCollider.h"

class OBBBoxCollider : public BaseCollider
{
public:
	OBBBoxCollider();
	virtual ~OBBBoxCollider();

	virtual void Update() override;
	virtual bool Intersects(Ray& ray, OUT float& distance) override;
	virtual bool Intersects(shared_ptr<BaseCollider>& other) override;
	virtual void RenderCollider(shared_ptr<class Shader> shader) override;
	virtual bool CalculatePenetraionDepth(shared_ptr<BaseCollider> other, Vec3& penetrationDepth) override;

	BoundingOrientedBox& GetBoundingBox() { return _boundingOrientedBox; }

private:	
	BoundingOrientedBox _boundingOrientedBox;
};


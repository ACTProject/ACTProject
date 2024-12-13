#pragma once
#include "BaseCollider.h"

class OBBBoxCollider : public BaseCollider
{
public:
	OBBBoxCollider();
	virtual ~OBBBoxCollider();

	virtual void Update() override;
	virtual bool Intersects(const Ray& ray, OUT float& distance) override;
	virtual bool Intersects(const shared_ptr<BaseCollider>& other) override;
	virtual bool Intersects(const BoundingBox& box) const override { return _boundingOrientedBox.Intersects(box); }
    virtual void RenderCollider(shared_ptr<class InstancingBuffer>& buffer) override;
    virtual void AppendVertices(vector<VertexPosData>& vertexData) const override {}
	virtual bool CalculatePenetraionDepth(shared_ptr<BaseCollider> other, Vec3& penetrationDepth) override;

	BoundingOrientedBox& GetBoundingBox() { return _boundingOrientedBox; }

private:	
	BoundingOrientedBox _boundingOrientedBox;
};


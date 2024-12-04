#pragma once
#include "BaseCollider.h"


class AABBBoxCollider : public BaseCollider
{
public:
	AABBBoxCollider();
	virtual ~AABBBoxCollider();

	virtual void Update() override;
	virtual bool Intersects(Ray& ray, OUT float& distance) override;
	virtual bool Intersects(const shared_ptr<BaseCollider>& other) override;
	virtual bool Intersects(const BoundingBox& box) const override { return _boundingBox.Intersects(box); }
    virtual void RenderCollider(shared_ptr<class InstancingBuffer>& buffer) override;
	virtual void AppendVertices(vector<VertexPosData>& vertexData) const override;
	virtual bool CalculatePenetraionDepth(shared_ptr<BaseCollider> other, Vec3& penetraionDepth) override;

	BoundingBox& GetBoundingBox() { return _boundingBox; }

private:
	BoundingBox _boundingBox;
};

#pragma once
#include "BaseCollider.h"

class SphereCollider : public BaseCollider
{
public:
	SphereCollider();
	virtual ~SphereCollider();

	virtual void Update() override;
	virtual bool Intersects(Ray& ray, OUT float& distance) override;
	virtual bool Intersects(const shared_ptr<BaseCollider>& other) override;
    virtual bool Intersects(const BoundingBox& box) const override { return _boundingSphere.Intersects(box); }
    virtual void RenderCollider(shared_ptr<class InstancingBuffer>& buffer) override;
	virtual void AppendVertices(vector<VertexPosData>& vertexData) const override;
	virtual bool CalculatePenetraionDepth(shared_ptr<BaseCollider> other, Vec3& penetrationDepth) override;

	void SetRadius(float radius) { _radius = radius; }
	BoundingSphere& GetBoundingSphere() { return _boundingSphere; }

private:
	float _radius = 1.f;
	BoundingSphere _boundingSphere;
};


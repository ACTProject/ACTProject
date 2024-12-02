#include "pch.h"
#include "AABBBoxCollider.h"
#include "SphereCollider.h"
#include "OBBBoxCollider.h"
#include "Geometry.h"

AABBBoxCollider::AABBBoxCollider() : BaseCollider(ColliderType::AABB)
{

}

AABBBoxCollider::~AABBBoxCollider()
{

}

void AABBBoxCollider::Update()
{
	_boundingBox.Center = GetColliderCenter();
}

bool AABBBoxCollider::Intersects(Ray& ray, OUT float& distance)
{
	return _boundingBox.Intersects(ray.position, ray.direction, OUT distance);
}

bool AABBBoxCollider::Intersects(shared_ptr<BaseCollider>& other)
{
	ColliderType type = other->GetColliderType();

	switch (type)
	{
	case ColliderType::Sphere:
		return _boundingBox.Intersects(dynamic_pointer_cast<SphereCollider>(other)->GetBoundingSphere());
	case ColliderType::AABB:
		return _boundingBox.Intersects(dynamic_pointer_cast<AABBBoxCollider>(other)->GetBoundingBox());
	case ColliderType::OBB:
		return _boundingBox.Intersects(dynamic_pointer_cast<OBBBoxCollider>(other)->GetBoundingBox());
	}
}

void AABBBoxCollider::RenderCollider(shared_ptr<class Shader> shader)
{
    Vec3 corners[BoundingBox::CORNER_COUNT];
    _boundingBox.GetCorners(corners);

	vector<VertexPosData> vertices = {
		{ corners[0] }, { corners[1] },
		{ corners[1] }, { corners[2] },
		{ corners[2] }, { corners[3] },
		{ corners[3] }, { corners[0] },
		{ corners[4] }, { corners[5] },
		{ corners[5] }, { corners[6] },
		{ corners[6] }, { corners[7] },
		{ corners[7] }, { corners[4] },
		{ corners[0] }, { corners[4] },
		{ corners[1] }, { corners[5] },
		{ corners[2] }, { corners[6] },
		{ corners[3] }, { corners[7] }
	};
    shared_ptr<VertexBuffer> vertexBuffer = make_shared<VertexBuffer>();
    vertexBuffer->Create(vertices, 0, true, false);
    vertexBuffer->PushData();

    DC->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
    shader->Draw(5, 0, static_cast<UINT>(vertices.size()), 0);
}

bool AABBBoxCollider::CalculatePenetraionDepth(shared_ptr<BaseCollider> other, Vec3& penetrationDepth)
{
	switch (other->GetColliderType())
	{
	case ColliderType::AABB:
		return CalculateAABBAABBCollision(this->_boundingBox, dynamic_pointer_cast<AABBBoxCollider>(other)->GetBoundingBox(), penetrationDepth);

	case ColliderType::Sphere:
		return CalculateAABBSphereCollision(this->_boundingBox, dynamic_pointer_cast<SphereCollider>(other)->GetBoundingSphere(), penetrationDepth);

	//case ColliderType::OBB:
		//return CalculateAABBOBBCollision(this->_boundingBox, dynamic_pointer_cast<OBBBoxCollider>(other)->GetBoundingBox(), penetrationDepth);

	default:
		return false;
	}
}


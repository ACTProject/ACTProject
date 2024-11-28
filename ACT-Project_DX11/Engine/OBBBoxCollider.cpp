#include "pch.h"
#include "OBBBoxCollider.h"
#include "SphereCollider.h"
#include "AABBBoxCollider.h"

OBBBoxCollider::OBBBoxCollider() : BaseCollider(ColliderType::OBB)
{

}

OBBBoxCollider::~OBBBoxCollider()
{

}

void OBBBoxCollider::Update()
{
	_boundingOrientedBox.Center = GetColliderCenter();
}

bool OBBBoxCollider::Intersects(Ray& ray, OUT float& distance)
{
	return _boundingOrientedBox.Intersects(ray.position, ray.direction, OUT distance);
}

bool OBBBoxCollider::Intersects(shared_ptr<BaseCollider>& other)
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

void OBBBoxCollider::RenderCollider(shared_ptr<class Shader> shader)
{
	Vec3 corners[BoundingOrientedBox::CORNER_COUNT];
	_boundingOrientedBox.GetCorners(corners);

	std::vector<VertexPosData> vertices = {
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

	auto vertexBuffer = std::make_shared<VertexBuffer>();
	vertexBuffer->Create(vertices, 0, true, false);
	vertexBuffer->PushData();

	DC->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
	shader->Draw(5, 0, static_cast<UINT>(vertices.size()), 0);
}

bool OBBBoxCollider::CalculatePenetraionDepth(shared_ptr<BaseCollider> other, Vec3& penetrationDepth)
{
	// TODO

	return false;
}

#include "pch.h"
#include "SphereCollider.h"
#include "AABBBoxCollider.h"
#include "OBBBoxCollider.h"

SphereCollider::SphereCollider()
	: BaseCollider(ColliderType::Sphere)
{

}

SphereCollider::~SphereCollider()
{

}

void SphereCollider::Update()
{
	_boundingSphere.Center = GetGameObject()->GetTransform()->GetPosition() + _offset;
}

bool SphereCollider::Intersects(Ray& ray, OUT float& distance)
{
	return _boundingSphere.Intersects(ray.position, ray.direction, OUT distance);
}

bool SphereCollider::Intersects(shared_ptr<BaseCollider>& other)
{
	ColliderType type = other->GetColliderType();

	switch (type)
	{
		case ColliderType::Sphere:
			return _boundingSphere.Intersects(dynamic_pointer_cast<SphereCollider>(other)->GetBoundingSphere());
		case ColliderType::AABB:
			return _boundingSphere.Intersects(dynamic_pointer_cast<AABBBoxCollider>(other)->GetBoundingBox());
		case ColliderType::OBB:
			return _boundingSphere.Intersects(dynamic_pointer_cast<OBBBoxCollider>(other)->GetBoundingBox());
	}

	return false;
}

void SphereCollider::RenderCollider(shared_ptr<class Shader> shader)
{
	vector<VertexPosData> vertices;

	const int latitudeSegments = 8; // 위도 방향 분할
	const int longitudeSegments = 8; // 경도 방향 분할

	// 위도 라인 (수평선)
	for (int i = 0; i <= latitudeSegments; ++i) {
		float phi = XM_PI * i / latitudeSegments; // 위도 각도
		float y = cos(phi) * _boundingSphere.Radius; // Y 좌표
		float radius = sin(phi) * _boundingSphere.Radius; // 해당 위도에서의 반지름

		for (int j = 0; j < longitudeSegments; ++j) {
			float theta = XM_2PI * j / longitudeSegments; // 경도 각도
			float nextTheta = XM_2PI * (j + 1) / longitudeSegments;

			Vec3 current = _boundingSphere.Center + Vec3(radius * cos(theta), y, radius * sin(theta));
			Vec3 next = _boundingSphere.Center + Vec3(radius * cos(nextTheta), y, radius * sin(nextTheta));

			vertices.push_back({ current });
			vertices.push_back({ next });
		}
	}

	// 경도 라인 (수직선)
	for (int i = 0; i < longitudeSegments; ++i) {
		float theta = XM_2PI * i / longitudeSegments; // 경도 각도
		float nextTheta = XM_2PI * (i + 1) / longitudeSegments;

		for (int j = 0; j < latitudeSegments; ++j) {
			float phi = XM_PI * j / latitudeSegments;
			float nextPhi = XM_PI * (j + 1) / latitudeSegments;

			Vec3 current = _boundingSphere.Center + Vec3(
				_boundingSphere.Radius * sin(phi) * cos(theta),
				_boundingSphere.Radius * cos(phi),
				_boundingSphere.Radius * sin(phi) * sin(theta)
			);

			Vec3 next = _boundingSphere.Center + Vec3(
				_boundingSphere.Radius * sin(nextPhi) * cos(theta),
				_boundingSphere.Radius * cos(nextPhi),
				_boundingSphere.Radius * sin(nextPhi) * sin(theta)
			);

			vertices.push_back({ current });
			vertices.push_back({ next });
		}
	}

	// 정점 버퍼 생성
	auto vertexBuffer = std::make_shared<VertexBuffer>();
	vertexBuffer->Create(vertices, 0, true, false);
	vertexBuffer->PushData();

	// 렌더링
	DC->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
	shader->Draw(5, 0, static_cast<UINT>(vertices.size()), 0);
}

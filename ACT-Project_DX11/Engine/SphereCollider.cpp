#include "pch.h"
#include "SphereCollider.h"
#include "AABBBoxCollider.h"
#include "OBBBoxCollider.h"
#include "Camera.h"

SphereCollider::SphereCollider()
	: BaseCollider(ColliderType::Sphere)
{

}

SphereCollider::~SphereCollider()
{

}

void SphereCollider::Update()
{
    if (Vec3(_boundingSphere.Center) == GetColliderCenter())
    {
        return;
    }
    else
    {
        _boundingSphere.Center = GetColliderCenter();
        OCTREE->UpdateCollider(GetGameObject()->GetCollider());
    }
}

bool SphereCollider::Intersects(const Ray& ray, OUT float& distance)
{
	return _boundingSphere.Intersects(ray.position, ray.direction, OUT distance);
}

bool SphereCollider::Intersects(const shared_ptr<BaseCollider>& other)
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

void SphereCollider::RenderCollider(shared_ptr<class InstancingBuffer>& buffer)
{
    vector<VertexPosData> vertexData; // 각 Collider의 정점 데이터
    shared_ptr<BaseCollider> collider = GetGameObject()->GetCollider();

    // 각 Collider의 정점 데이터를 추가
    collider->AppendVertices(vertexData);

    auto vertexBuffer = std::make_shared<VertexBuffer>();
    vertexBuffer->Create(vertexData, 0, true, false);
    vertexBuffer->PushData();

    // 셰이더 설정
    shared_ptr<Shader> shader = make_shared<Shader>(L"23. RenderDemo.fx");

    // GlobalData
    if (GetGameObject()->GetLayerIndex() == LayerMask::Layer_UI)
        shader->PushGlobalData(Camera::S_UIMatView, Camera::S_UIMatProjection);
    else
        shader->PushGlobalData(Camera::S_MatView, Camera::S_MatProjection);

    // 버퍼 바인딩
    vertexBuffer->PushData();
    buffer->PushData();

    // 인스턴싱 렌더링
    DC->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
    shader->DrawInstanced(5, 0, static_cast<UINT>(vertexData.size()), buffer->GetCount());
}

void SphereCollider::AppendVertices(vector<VertexPosData>& vertexData) const
{
    const int latitudeSegments = 8; // 위도 방향 분할
    const int longitudeSegments = 8; // 경도 방향 분할

    // 중심 좌표 계산 (중심 + offset)
    Vec3 centerWithOffset = _boundingSphere.Center;

    // 위도 라인 (수평선)
    for (int i = 0; i <= latitudeSegments; ++i) {
        float phi = XM_PI * i / latitudeSegments; // 위도 각도
        float y = cos(phi) * _boundingSphere.Radius; // Y 좌표
        float radius = sin(phi) * _boundingSphere.Radius; // 해당 위도에서의 반지름

        for (int j = 0; j < longitudeSegments; ++j) {
            float theta = XM_2PI * j / longitudeSegments; // 경도 각도
            float nextTheta = XM_2PI * (j + 1) / longitudeSegments;

            Vec3 current = Vec3(radius * cos(theta), y, radius * sin(theta));     // 로컬 좌표
            Vec3 next = Vec3(radius * cos(nextTheta), y, radius * sin(nextTheta)); // 로컬 좌표

            vertexData.push_back({ current });
            vertexData.push_back({ next });
        }
    }

    // 경도 라인 (수직선)
    for (int i = 0; i < longitudeSegments; ++i) {
        float theta = XM_2PI * i / longitudeSegments; // 경도 각도
        float nextTheta = XM_2PI * (i + 1) / longitudeSegments;

        for (int j = 0; j < latitudeSegments; ++j) {
            float phi = XM_PI * j / latitudeSegments;
            float nextPhi = XM_PI * (j + 1) / latitudeSegments;

            Vec3 current = Vec3(
                _boundingSphere.Radius * sin(phi) * cos(theta),
                _boundingSphere.Radius * cos(phi),
                _boundingSphere.Radius * sin(phi) * sin(theta)
            ); // 로컬 좌표

            Vec3 next = Vec3(
                _boundingSphere.Radius * sin(nextPhi) * cos(theta),
                _boundingSphere.Radius * cos(nextPhi),
                _boundingSphere.Radius * sin(nextPhi) * sin(theta)
            ); // 로컬 좌표

            vertexData.push_back({ current });
            vertexData.push_back({ next });
        }
    }
}


bool SphereCollider::CalculatePenetraionDepth(shared_ptr<BaseCollider> other, Vec3& penetrationDepth)
{
	switch (other->GetColliderType())
	{
	case ColliderType::AABB:
		return CalculateAABBSphereCollision(dynamic_pointer_cast<AABBBoxCollider>(other)->GetBoundingBox(), this->_boundingSphere, penetrationDepth);

	case ColliderType::Sphere:
		return CalculateSphereSphereCollision(this->_boundingSphere, dynamic_pointer_cast<SphereCollider>(other)->GetBoundingSphere(), penetrationDepth);

	//case ColliderType::OBB:
		//return CalculateOBBSphereCollision(dynamic_pointer_cast<OBBBoxCollider>(other)->GetBoundingBox(), this->_boundingSphere, penetrationDepth);

	default:
		return false;
	}

}

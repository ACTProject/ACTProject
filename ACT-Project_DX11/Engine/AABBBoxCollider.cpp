#include "pch.h"
#include "AABBBoxCollider.h"
#include "SphereCollider.h"
#include "OBBBoxCollider.h"
#include "Geometry.h"
#include "Camera.h"

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

bool AABBBoxCollider::Intersects(const Ray& ray, OUT float& distance)
{
	// Collider가 비활성화 상태이면 충돌 검사 중단
	if (!this->IsActive())
		return false;

	return _boundingBox.Intersects(ray.position, ray.direction, OUT distance);
}

bool AABBBoxCollider::Intersects(const shared_ptr<BaseCollider>& other)
{
	// Collider가 비활성화 상태이면 충돌 검사 중단
	if (!this->IsActive() || !other->IsActive())
		return false;

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

void AABBBoxCollider::RenderCollider(shared_ptr<class InstancingBuffer>& buffer)
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

void AABBBoxCollider::AppendVertices(vector<VertexPosData>& vertexData) const
{
    Vec3 corners[BoundingBox::CORNER_COUNT];
    _boundingBox.GetCorners(corners);

    // AABB 중심 계산
    Vec3 center = _boundingBox.Center;

    // 모든 정점에서 중심을 빼서 로컬 좌표로 변환
    Vec3 localCorners[BoundingBox::CORNER_COUNT];
    for (int i = 0; i < BoundingBox::CORNER_COUNT; ++i)
    {
        localCorners[i] = corners[i] - center; // 로컬 좌표 계산
    }

    // 로컬 좌표를 사용하여 정점 데이터 생성
    vector<VertexPosData> vertices = {
        { localCorners[0] }, { localCorners[1] },
        { localCorners[1] }, { localCorners[2] },
        { localCorners[2] }, { localCorners[3] },
        { localCorners[3] }, { localCorners[0] },
        { localCorners[4] }, { localCorners[5] },
        { localCorners[5] }, { localCorners[6] },
        { localCorners[6] }, { localCorners[7] },
        { localCorners[7] }, { localCorners[4] },
        { localCorners[0] }, { localCorners[4] },
        { localCorners[1] }, { localCorners[5] },
        { localCorners[2] }, { localCorners[6] },
        { localCorners[3] }, { localCorners[7] }
    };

    vertexData.insert(vertexData.end(), vertices.begin(), vertices.end());
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


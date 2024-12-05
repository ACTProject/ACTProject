#include "pch.h"
#include "OctreeNode.h"
#include "BaseCollider.h"
#include "AABBBoxCollider.h"
#include "Camera.h"

OctreeNode::OctreeNode(const BoundingBox& bounds, int depth, int maxDepth)
	: _bounds(bounds), _depth(depth), _maxDepth(maxDepth)
{
}

OctreeNode::~OctreeNode()
{
}

//bool OctreeNode::InsertTerrain(const TerrainTriangle& triangle)
//{
//	if (!_bounds.Intersects(triangle.GetBoundingBox()))
//		return false;
//
//	if (_children.empty() && _depth < _maxDepth)
//	{
//		_terrainData.push_back(triangle);
//
//		if (_terrainData.size() > MAX_OBJECTS)
//		{
//			Subdivide();
//			for (auto it = _terrainData.begin(); it != _terrainData.end();)
//			{
//				bool inserted = false;
//				for (auto& child : _children)
//				{
//					if (child->InsertTerrain(*it))
//					{
//						it = _terrainData.erase(it);
//						inserted = true;
//						break;
//					}
//				}
//				if (!inserted)
//					++it;
//			}
//		}
//		return true;
//	}
//
//	for (auto& child : _children)
//	{
//		if (child->InsertTerrain(triangle))
//			return true;
//	}
//
//	_terrainData.push_back(triangle);
//	return true;
//}

// Collider를 현재 노드 또는 하위 노드에 삽입합니다
bool OctreeNode::InsertCollider(shared_ptr<BaseCollider>& collider)
{
/* - 작동 방식 -
   1. 경계 확인 : Collider가 노드의 바운딩박스에 포함되지 않으면 삽입 x
   2. 리프 노드 처리 : 자식 노드가 없고 최대 깊이에 도달하지 않았으면 Collider를 현재 노드에 추가
   3. 노드 분할 : Collider 수가 MAX_OBJECTS를 초과하면 8개로 분할
   4. 자식 노드에 삽입 : Collider가 어느 자식 노드에 속하는지 확인 후, 해당 노드에 삽입.
*/

    // Collider가 현재 노드의 경계와 충돌하지 않으면 삽입하지 않음
	if (!collider->Intersects(_bounds))
		return false;

    // 리프 노드 처리
	if (_children.empty() && _depth < _maxDepth)
	{
		_colliders.push_back(collider);

        // 최대 Collider 수 초과 시 분할
		if (_colliders.size() > MAX_OBJECTS)
		{
			Subdivide();
			for (auto it = _colliders.begin(); it != _colliders.end();)
			{
				bool inserted = false;
				for (auto& child : _children)
				{
					if (child->InsertCollider(*it))
					{
						it = _colliders.erase(it);
						inserted = true;
						break;
					}
				}
				if (!inserted)
					++it;
			}
		}
		return true;
	}

    // 자식 노드에 삽입
	for (auto& child : _children)
	{
		if (child->InsertCollider(collider))
			return true;
	}

    // 삽입 실패 시 현재 노드에 저장
	_colliders.push_back(collider);
	return true;
}

//std::vector<TerrainTriangle> OctreeNode::QueryTerrain(const BaseCollider& rangeCollider)
//{
//	std::vector<TerrainTriangle> result;
//
//	if (!rangeCollider.Intersects(std::make_shared<AABBBoxCollider>(_bounds)))
//		return result;
//
//	for (const auto& triangle : _terrainData)
//	{
//		if (rangeCollider.Intersects(triangle.GetBoundingBox()))
//		{
//			result.push_back(triangle);
//		}
//	}
//
//	if (!_children.empty())
//	{
//		for (const auto& child : _children)
//		{
//			auto childResult = child->QueryTerrain(rangeCollider);
//			result.insert(result.end(), childResult.begin(), childResult.end());
//		}
//	}
//
//	return result;
//}

// 범위 Collider와 충돌하는 Collider를 검색
std::vector<std::shared_ptr<BaseCollider>> OctreeNode::QueryColliders(const shared_ptr<BaseCollider>& rangeCollider)
{
/* - 작동 방식 -
   1. 경계 확인 : rangeCollider가 노드의 바운딩박스와 충돌하지 않으면 검색 중단
   2. Collider 충돌 검사 : 노드에 저장된 모든 Collider와 rangeCollider 간 충돌 여부를 확인.
   3. 자식 노드 검색 : 자식 노드가 있으면 재귀적으로 검색.
   4. 결과 반환 : 충돌하는 Collider를 std::vector로 반환.
*/
	std::vector<std::shared_ptr<BaseCollider>> result;

    // 범위 Collider가 현재 노드와 충돌하지 않으면 검색 중단
	if (!rangeCollider->Intersects(_bounds))
		return result;

    // 현재 노드에 저장된 Collider와 충돌 검사
	for (const auto& collider : _colliders)
	{
		if (rangeCollider->Intersects(collider))
		{
			result.push_back(collider);
		}
	}

    // 자식 노드 검색
	if (!_children.empty())
	{
		for (const auto& child : _children)
		{
			auto childResult = child->QueryColliders(rangeCollider);
			result.insert(result.end(), childResult.begin(), childResult.end());
		}
	}

	return result;
}

void OctreeNode::RenderNode()
{
    // 1. 현재 노드의 경계 박스 생성
    Vec3 corners[BoundingBox::CORNER_COUNT];
    _bounds.GetCorners(corners);

    // 로컬 좌표로 변환
    Vec3 center = _bounds.Center;

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

    // 2. VertexBuffer 생성
    auto vertexBuffer = std::make_shared<VertexBuffer>();
    vertexBuffer->Create(vertices, 0, true, false);
    vertexBuffer->PushData();

    // 3. 셰이더 설정
    auto shader = std::make_shared<Shader>(L"23. RenderDemo.fx");
    shader->PushGlobalData(Camera::S_MatView, Camera::S_MatProjection);

    // 4. 렌더링
    DC->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
    shader->Draw(5, 1, static_cast<UINT>(vertices.size()), 0);

    // 기본 토폴로지 복구
    DC->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    // 5. 자식 노드 렌더링
    for (const auto& child : _children)
    {
        if (child)
        {
            child->RenderNode();
        }
    }
}

// 현재 노드를 8개의 자식 노드로 분할
void OctreeNode::Subdivide()
{
/* - 작동 방식 - 
   1. 현재 노드의 경계를 중심으로 8개의 작은 경계(BoundingBox) 생성
   2. 각 경계를 사용하여 자식 노드를 생성
   3. 자식 노드는 현재 노드보다 한 단계 더 깊은(_depth + 1) 노드로 설정
*/
    Vec3 Extents = _bounds.Extents;
    Extents /= 2.0f;

    Vec3 halfSize = Extents;
	Vec3 center = _bounds.Center;

	_children.push_back(std::make_unique<OctreeNode>(BoundingBox(center + Vec3(-halfSize.x, -halfSize.y, -halfSize.z), halfSize), _depth + 1, _maxDepth));
	_children.push_back(std::make_unique<OctreeNode>(BoundingBox(center + Vec3(halfSize.x, -halfSize.y, -halfSize.z), halfSize), _depth + 1, _maxDepth));
	_children.push_back(std::make_unique<OctreeNode>(BoundingBox(center + Vec3(-halfSize.x, halfSize.y, -halfSize.z), halfSize), _depth + 1, _maxDepth));
	_children.push_back(std::make_unique<OctreeNode>(BoundingBox(center + Vec3(halfSize.x, halfSize.y, -halfSize.z), halfSize), _depth + 1, _maxDepth));
	_children.push_back(std::make_unique<OctreeNode>(BoundingBox(center + Vec3(-halfSize.x, -halfSize.y, halfSize.z), halfSize), _depth + 1, _maxDepth));
	_children.push_back(std::make_unique<OctreeNode>(BoundingBox(center + Vec3(halfSize.x, -halfSize.y, halfSize.z), halfSize), _depth + 1, _maxDepth));
	_children.push_back(std::make_unique<OctreeNode>(BoundingBox(center + Vec3(-halfSize.x, halfSize.y, halfSize.z), halfSize), _depth + 1, _maxDepth));
	_children.push_back(std::make_unique<OctreeNode>(BoundingBox(center + Vec3(halfSize.x, halfSize.y, halfSize.z), halfSize), _depth + 1, _maxDepth));
}
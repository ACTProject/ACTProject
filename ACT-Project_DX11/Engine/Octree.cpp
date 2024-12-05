#include "pch.h"
#include "Octree.h"

void Octree::Init(const BoundingBox& worldBounds, int maxDepth)
{
    // 기존 루트 노드 제거
    Clear();
    _root = std::make_unique<OctreeNode>(worldBounds, 0, maxDepth);
}

void Octree::Clear()
{
    // 루트 노드를 초기화하여 메모리 해제
    _root.reset();
}

//void Octree::InsertTerrain(const TerrainTriangle& triangle)
//{
//	if (_root)
//	{
//		_root->InsertTerrain(triangle);
//	}
//}

void Octree::InsertCollider(std::shared_ptr<BaseCollider> collider)
{
    if (_root)
    {
        _root->InsertCollider(collider);
    }
}

//std::vector<TerrainTriangle> Octree::QueryTerrain(const BaseCollider& rangeCollider)
//{
//	if (_root)
//	{
//		return _root->QueryTerrain(rangeCollider);
//	}
//	return {};
//}

std::vector<std::shared_ptr<BaseCollider>> Octree::QueryColliders(const shared_ptr<BaseCollider>& rangeCollider)
{
    if (_root)
    {
        return _root->QueryColliders(rangeCollider);
    }
    return {};
}

void Octree::RenderOctree()
{
    if (!(DEBUG->IsDebugEnabled() || INPUT->GetButton(KEY_TYPE::CAPSLOCK)))
        return;

    if (_root)
        _root->RenderNode();
}
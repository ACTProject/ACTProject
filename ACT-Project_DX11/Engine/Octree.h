#pragma once
#include "OctreeNode.h"

class Octree
{
    DECLARE_SINGLE(Octree);

public:
    void Init(const BoundingBox& worldBounds, int maxDepth);

    // 루트 노드 초기화 해제
    void Clear();

    // Terrain 데이터 삽입
   // void InsertTerrain(const TerrainTriangle& triangle);

    // Collider 삽입
    void InsertCollider(std::shared_ptr<BaseCollider> collider);

    // 범위 내 Terrain 데이터 검색
   // std::vector<TerrainTriangle> QueryTerrain(const BaseCollider& rangeCollider);

    // 범위 내 Collider 검색
    std::vector<std::shared_ptr<BaseCollider>> QueryColliders(const shared_ptr<BaseCollider>& rangeCollider);

    void RenderOctree();
private:
    std::unique_ptr<OctreeNode> _root; // 루트 노드
};

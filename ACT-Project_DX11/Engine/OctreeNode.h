#pragma once
/*
    **경계(Box)**를 기준으로 3D 공간을 정의.
    Collider 데이터를 저장하고 관리.
    저장된 데이터가 많아지면 하위 노드(Children Nodes)로 분할(Subdivide).
    특정 범위 내 Collider를 효율적으로 검색(Query).
*/

class BaseCollider;

class OctreeNode
{
public:
    OctreeNode(const BoundingBox& bounds, int depth, int maxDepth);
    ~OctreeNode();

    // 데이터 삽입
   // bool InsertTerrain(const TerrainTriangle& triangle);
    bool InsertCollider(shared_ptr<BaseCollider>& collider);

    // 범위 검색
   // std::vector<TerrainTriangle> QueryTerrain(const BaseCollider& rangeCollider);
    std::vector<std::shared_ptr<BaseCollider>> QueryColliders(const shared_ptr<BaseCollider>& rangeCollider);

private:
    void Subdivide();

private:
    BoundingBox _bounds; // 현재 노드가 관리하는 공간
  //  std::vector<TerrainTriangle> _terrainData; // Terrain 삼각형 데이터
    std::vector<std::shared_ptr<BaseCollider>> _colliders; // 현재 노드에 저장된 Collider의 목록
    std::vector<std::unique_ptr<OctreeNode>> _children; // 현재 노드의 자식 노드 목록
    int _depth; // 현재 노드 깊이
    int _maxDepth; // Octree의 최대 깊이로, 더 이상 분할하지 않는 기준
    static const int MAX_OBJECTS = 8; // 노드가 저장할 수 있는 최대 Collider 수 (이 값을 초과하면 노드를 8개로 분할)
};

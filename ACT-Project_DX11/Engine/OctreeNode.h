#pragma once

class BaseCollider;

class OctreeNode
{
//public:
//	OctreeNode(const BoundingBox& bounds, int depth, int maxDepth);
//	~OctreeNode();
//
//	// 데이터 삽입
//	//bool InsertTerrain(const TerrainTriangle& triangle);
//	bool InsertCollider(std::shared_ptr<BaseCollider> collider);
//
//	// 범위 검색
//	//std::vector<TerrainTriangle> QueryTerrain(const BaseCollider& rangeCollider);
//	std::vector<std::shared_ptr<BaseCollider>> QueryColliders(const BaseCollider& rangeCollider);
//
//private:
//	void Subdivide();
//
//private:
//	BoundingBox _bounds; // 노드의 경계 (AABB)
//	//std::vector<TerrainTriangle> _terrainData; // Terrain 삼각형 데이터
//	std::vector<std::shared_ptr<BaseCollider>> _colliders; // Collider 데이터
//	std::vector<std::unique_ptr<OctreeNode>> _children; // 자식 노드
//	int _depth; // 현재 노드 깊이
//	int _maxDepth; // 최대 깊이
//	static const int MAX_OBJECTS = 8; // 노드당 최대 오브젝트 수
};
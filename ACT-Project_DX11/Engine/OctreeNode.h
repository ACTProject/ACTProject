#pragma once

class BaseCollider;

class OctreeNode
{
//public:
//	OctreeNode(const BoundingBox& bounds, int depth, int maxDepth);
//	~OctreeNode();
//
//	// 占쏙옙占쏙옙占쏙옙 占쏙옙占쏙옙
//	//bool InsertTerrain(const TerrainTriangle& triangle);
//	bool InsertCollider(std::shared_ptr<BaseCollider> collider);
//
//	// 占쏙옙占쏙옙 占싯삼옙
//	//std::vector<TerrainTriangle> QueryTerrain(const BaseCollider& rangeCollider);
//	std::vector<std::shared_ptr<BaseCollider>> QueryColliders(const BaseCollider& rangeCollider);
//
//private:
//	void Subdivide();
//
//private:
//	BoundingBox _bounds; // 占쏙옙占쏙옙占?占쏙옙占?(AABB)
//	//std::vector<TerrainTriangle> _terrainData; // Terrain 占쏙각占쏙옙 占쏙옙占쏙옙占쏙옙
//	std::vector<std::shared_ptr<BaseCollider>> _colliders; // Collider 占쏙옙占쏙옙占쏙옙
//	std::vector<std::unique_ptr<OctreeNode>> _children; // 占쌘쏙옙 占쏙옙占?
//	int _depth; // 占쏙옙占쏙옙 占쏙옙占?占쏙옙占쏙옙
//	int _maxDepth; // 占쌍댐옙 占쏙옙占쏙옙
//	static const int MAX_OBJECTS = 8; // 占쏙옙占쏙옙 占쌍댐옙 占쏙옙占쏙옙占쏙옙트 占쏙옙
};

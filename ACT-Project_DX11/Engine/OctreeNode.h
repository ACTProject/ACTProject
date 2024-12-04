#pragma once

class BaseCollider;

class OctreeNode
{
//public:
//	OctreeNode(const BoundingBox& bounds, int depth, int maxDepth);
//	~OctreeNode();
//
//	// ������ ����
//	//bool InsertTerrain(const TerrainTriangle& triangle);
//	bool InsertCollider(std::shared_ptr<BaseCollider> collider);
//
//	// ���� �˻�
//	//std::vector<TerrainTriangle> QueryTerrain(const BaseCollider& rangeCollider);
//	std::vector<std::shared_ptr<BaseCollider>> QueryColliders(const BaseCollider& rangeCollider);
//
//private:
//	void Subdivide();
//
//private:
//	BoundingBox _bounds; // ����� ��� (AABB)
//	//std::vector<TerrainTriangle> _terrainData; // Terrain �ﰢ�� ������
//	std::vector<std::shared_ptr<BaseCollider>> _colliders; // Collider ������
//	std::vector<std::unique_ptr<OctreeNode>> _children; // �ڽ� ���
//	int _depth; // ���� ��� ����
//	int _maxDepth; // �ִ� ����
//	static const int MAX_OBJECTS = 8; // ���� �ִ� ������Ʈ ��
};

#include "pch.h"
#include "OctreeManager.h"

Octree::Octree(const BoundingBox& worldBounds, int maxDepth)
{
	_root = std::make_unique<OctreeNode>(worldBounds, 0, maxDepth);
}

Octree::~Octree()
{
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

std::vector<std::shared_ptr<BaseCollider>> Octree::QueryColliders(const BaseCollider& rangeCollider)
{
	if (_root)
	{
		return _root->QueryColliders(rangeCollider);
	}
	return {};
}
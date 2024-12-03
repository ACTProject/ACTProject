#include "pch.h"
#include "OctreeNode.h"
#include "BaseCollider.h"

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

bool OctreeNode::InsertCollider(std::shared_ptr<BaseCollider> collider)
{
	if (!collider->Intersects(std::make_shared<AABBBoxCollider>(_bounds)))
		return false;

	if (_children.empty() && _depth < _maxDepth)
	{
		_colliders.push_back(collider);

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

	for (auto& child : _children)
	{
		if (child->InsertCollider(collider))
			return true;
	}

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

std::vector<std::shared_ptr<BaseCollider>> OctreeNode::QueryColliders(const BaseCollider& rangeCollider)
{
	std::vector<std::shared_ptr<BaseCollider>> result;

	if (!rangeCollider.Intersects(std::make_shared<AABBBoxCollider>(_bounds)))
		return result;

	for (const auto& collider : _colliders)
	{
		if (rangeCollider.Intersects(collider))
		{
			result.push_back(collider);
		}
	}

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

void OctreeNode::Subdivide()
{
	Vec3 halfSize = _bounds.Extents / 2.0f;
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
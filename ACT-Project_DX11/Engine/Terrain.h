#pragma once
#include "Component.h"

class Terrain : public Component
{
	using Super = Component;

public:
	Terrain();
	~Terrain();

	int32 GetSizeX() { return _sizeX; }
	int32 GetSizeZ() { return _sizeZ; }
	shared_ptr<Mesh> GetMesh() { return _mesh; }

	void Create(int32 sizeX, int32 sizeZ, shared_ptr<Material> material);
	bool Pick(int32 screenX, int32 screenY, Vec3& pickPos, float& distance);
	// 충돌 감지용 함수
	float GetHeightAtPosition(float x, float z) const;

private:
	shared_ptr<Mesh> _mesh;
	int32 _sizeX = 0;
	int32 _sizeZ = 0;
};


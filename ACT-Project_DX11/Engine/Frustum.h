#pragma once

enum PLANE_TYPE : uint8
{
	PLANE_FRONT,
	PLANE_BACK,
	PLANE_UP,
	PLANE_DOWN,
	PLANE_LEFT,
	PLANE_RIGHT,

	PLANE_END
};

class Frustum
{
    DECLARE_SINGLE(Frustum);
public:
	void FinalUpdate();
	bool ContainsSphere(const Vec3& pos, float radius);
    bool ContainsAABB(const BoundingBox& box) const;

private:
	array<Vec4, PLANE_END> _planes; // 프러스텀의 6개 평면
};


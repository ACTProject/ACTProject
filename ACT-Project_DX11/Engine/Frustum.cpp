#include "pch.h"
#include "Frustum.h"
#include "Camera.h"

void Frustum::FinalUpdate()
{
	Matrix matViewInv = Camera::S_MatView.Invert();
	Matrix matProjectionInv = Camera::S_MatProjection.Invert();
    // 뷰-투영 행렬의 역행렬 계산
	Matrix viewProjInverse = matProjectionInv * matViewInv;

    // NDC(정규화된 장치 좌표계)의 8개 코너를 월드 공간으로 변환
	vector<Vec3> worldCorners =
	{
        ::XMVector3TransformCoord(Vec3(-1.f,  1.f, 0.f), viewProjInverse), // Near Top Left
        ::XMVector3TransformCoord(Vec3(1.f,  1.f, 0.f), viewProjInverse), // Near Top Right
        ::XMVector3TransformCoord(Vec3(1.f, -1.f, 0.f), viewProjInverse), // Near Bottom Right
        ::XMVector3TransformCoord(Vec3(-1.f, -1.f, 0.f), viewProjInverse), // Near Bottom Left
        ::XMVector3TransformCoord(Vec3(-1.f,  1.f, 1.f), viewProjInverse), // Far Top Left
        ::XMVector3TransformCoord(Vec3(1.f,  1.f, 1.f), viewProjInverse), // Far Top Right
        ::XMVector3TransformCoord(Vec3(1.f, -1.f, 1.f), viewProjInverse), // Far Bottom Right
        ::XMVector3TransformCoord(Vec3(-1.f, -1.f, 1.f), viewProjInverse)  // Far Bottom Left
	};

    // 프러스텀 평면 설정
	_planes[PLANE_FRONT] =   ::XMPlaneFromPoints(worldCorners[0], worldCorners[1], worldCorners[2]); // Near CW
	_planes[PLANE_BACK]  =   ::XMPlaneFromPoints(worldCorners[4], worldCorners[7], worldCorners[5]); // Far CCW
	_planes[PLANE_UP]    =   ::XMPlaneFromPoints(worldCorners[4], worldCorners[5], worldCorners[1]); // Top CW
	_planes[PLANE_DOWN]  =   ::XMPlaneFromPoints(worldCorners[7], worldCorners[3], worldCorners[6]); // Bottom CCW
	_planes[PLANE_LEFT]  =   ::XMPlaneFromPoints(worldCorners[4], worldCorners[0], worldCorners[7]); // Left CW
	_planes[PLANE_RIGHT] =   ::XMPlaneFromPoints(worldCorners[5], worldCorners[6], worldCorners[1]); // Right CCW
}

// 구체(Sphere)가 프러스텀 안에 포함되어 있는지 확인
bool Frustum::ContainsSphere(const Vec3& pos, float radius)
{
    // 프러스텀의 각 평면을 검사
	for (const Vec4& plane : _planes)
	{
        // 평면의 법선 벡터와 거리 추출
		Vec3 normal = Vec3(plane.x, plane.y, plane.z);
        float distanceToPlane = normal.Dot(pos) + plane.w;
		
        // 구체의 반지름보다 먼 경우 프러스텀 밖에 있음
		if (distanceToPlane > radius)
			return false;
	}

	return true; // 모든 평면을 통과하면 프러스텀 안에 있음
}

// AABB가 프러스텀 안에 포함되어 있는지 확인
bool Frustum::ContainsAABB(const BoundingBox& box) const
{

    // AABB의 모든 코너 검사
    for (const Vec4& plane : _planes)
    {
        Vec3 normal(plane.x, plane.y, plane.z);
        bool outside = true;

        Vec3 corners[BoundingBox::CORNER_COUNT];
        box.GetCorners(corners);

        for (const Vec3& corner : corners)
        {
            if (normal.Dot(corner) + plane.w < 0)
            {
                outside = false;
                break; // 한 점이라도 평면의 안쪽에 있으면 종료
            }
        }

        if (outside)
            return false; // 평면 바깥에 있음
    }

    return true; // 모든 평면 안쪽에 있음
}

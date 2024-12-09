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

    // 패딩 적용 (10 유닛)
    ExpandFrustum(1.0f);
}

void Frustum::ExpandFrustum(float padding)
{
    for (Vec4& plane : _planes)
    {
        Vec3 normal(plane.x, plane.y, plane.z);
        plane.w -= normal.Length() * padding; // 평면의 법선 방향으로 패딩 추가
    }
}

bool Frustum::ContainsAABB(const BoundingBox& box, float threshold) const
{
    Vec3 corners[BoundingBox::CORNER_COUNT];
    box.GetCorners(corners); // AABB 코너 가져오기

    int insideCount = 0;

    for (const Vec4& plane : _planes)
    {
        Vec3 normal(plane.x, plane.y, plane.z);
        bool allOutside = true;

        for (const Vec3& corner : corners)
        {
            float distance = normal.Dot(corner) + plane.w;

            // 한 점이라도 안쪽이면 프러스텀에 포함
            if (distance >= -threshold)
            {
                allOutside = false;
                insideCount++;
                break;
            }
        }

        if (allOutside)
            return false; // 완전히 바깥에 있음
    }

    return insideCount > 0; // 일부라도 포함되어 있으면 true
}

bool Frustum::ContainsSphere(const Vec3& pos, float radius, float threshold) const
{
    for (const Vec4& plane : _planes)
    {
        Vec3 normal = Vec3(plane.x, plane.y, plane.z);
        float distanceToPlane = normal.Dot(pos) + plane.w;

        // 반지름과 threshold를 고려
        if (distanceToPlane < -(radius + threshold))
            return false; // 완전히 밖에 있음
    }

    return true; // 일부라도 포함
}


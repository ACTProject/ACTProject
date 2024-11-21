#include "pch.h"
#include "Rangoon.h"



void Rangoon::Aggro(Vec3& s, Vec3& t)
{

}

void Rangoon::Move(Vec3& pos, const Vec3& targetPos)
{
    Vec3 direction = targetPos - pos;  // 목표 위치 방향 계산
    float distance = direction.Length();    // 목표와의 거리
    direction.Normalize();  // 방향 벡터를 단위 벡터로 정규화

    // 목표에 도달했거나 가까워지면 목표에 정확히 도달
    if (distance < _speed * _deltaTime) {
        pos = targetPos; // 목표에 도달
    }
    else {
        pos += direction * _speed * _deltaTime;  // 일정 거리만큼 이동
    }
}
void Rangoon::Tracking(Vec3 pos, const std::vector<Node3D>& path)
{
    if (path.empty()) {
        return;
    }

    // 경로 상의 각 노드를 따라 이동
    for (size_t i = 0; i < path.size(); ++i) {
        // 현재 위치가 목표 노드에 도달했다면 다음 노드로 이동
        if (i + 1 < path.size()) {
            Move(pos, path[i + 1].pos);
        }
    }

}

void Rangoon::Attack()
{

}

void Rangoon::Start()
{

}

void Rangoon::Update()
{
    Node3D start = { enemy->GetOrAddTransform()->GetPosition(), 0, 0, nullptr };
    Node3D goal = { {0,0,0},0,0,nullptr };
    
    std::vector<Node3D> path = astar.findPath(start, goal);

    Tracking(enemy->GetTransform()->GetPosition(), path);
}
#include "pch.h"
#include "RangoonScript.h"

void RangoonScript::Aggro(Vec3& s, Vec3& t)
{

}

void RangoonScript::Move(const Vec3 targetPos)
{
    //y축 회전이다.
    _transform = GetTransform();
    direction = targetPos - _transform->GetPosition();  // 목표 위치 방향 계산
    distance = direction.Length();    // 목표와의 거리
    if (distance < 5.f) {
        return; // 목표에 도달
    }
    direction.Normalize();  // 방향 벡터를 단위 벡터로 정규화

    _transform->SetPosition(_transform->GetPosition() + direction * _speed * _deltaTime);  // 일정 거리만큼 이동
}

void RangoonScript::Rota(const Vec3 targetPos)
{
    CurForward = _transform->GetLook();
    if (CurForward.z > 0)
        int a = 0;
    direction = targetPos - _transform->GetPosition();
    direction.Normalize();

    // 외적을 이용한 회전 축 계산
    Vec3 rotationAxis = CurForward.Cross(direction);

    // 외적 결과가 매우 작으면 방향 차이가 거의 없으므로 회전 필요 없음
    if (rotationAxis.LengthSquared() < 1e-6f)
    {
        return;
    }

    rotationAxis.Normalize();

    // 각도 계산
    float angle = std::acos(CurForward.Dot(direction));

    // 작은 각도는 무시
    if (abs(angle) < 0.01f) // 0.01 라디안(약 0.57도) 이하 회전 무시
    {
        return;
    }
    // 방향에 따라 각도 조정 (y축 중심 회전)
    if (rotationAxis.y < 0) {
        angle = -angle;  // 왼쪽 회전
    }

    // 현재 회전값 업데이트
    Vec3 currentRotation = _transform->GetLocalRotation();
    _transform->SetRotation(currentRotation + Vec3(0, angle, 0));
   
}

void RangoonScript::Tracking(Vec3 pos, const std::vector<Node3D>& path)
{
    if (path.empty()) {
        return;
    }

    // 경로 상의 각 노드를 따라 이동
    for (size_t i = 0; i < path.size(); ++i) {
        // 현재 위치가 목표 노드에 도달했다면 다음 노드로 이동
        if (i + 1 < path.size()) {
            Move(path[i + 1].pos);
        }
    }
}




void RangoonScript::Attack()
{

}

void RangoonScript::Start()
{

}

void RangoonScript::Update()
{
    _transform = GetTransform();
    _player = SCENE->GetCurrentScene()->GetPlayer();
    Vec3 playerPosition = _player->GetTransform()->GetPosition();

    //Node3D start = { _transform->GetPosition(), 0, 0, nullptr };
    //Node3D goal = { {0,0,0},0,0,nullptr };
    
    //std::vector<Node3D> path = astar.findPath(start, goal);

    //Tracking(_transform->GetPosition(), path);
    //if (INPUT->GetButton(KEY_TYPE::KEY_4))
    {
        Move(playerPosition);
        Rota(playerPosition);
    }
    
}


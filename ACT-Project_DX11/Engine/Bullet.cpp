#include "pch.h"
#include "Bullet.h"

Bullet::Bullet() : Super(ComponentType::Bullet)
{

}

Bullet::~Bullet()
{

}

void Bullet::Update()
{
    Shooting();
}

void Bullet::Shooting()
{
    if (FirstTime)
    {
        _player = SCENE->GetCurrentScene()->GetPlayer();
        PlayerPos = _player->GetTransform()->GetPosition();
    }

    _transform = GetTransform();
    float dt = TIME->GetDeltaTime();
    Vec3 pos = _transform->GetPosition();
    float distance = sqrt(powf(pos.x - PlayerPos.x, 2) + powf(pos.z - PlayerPos.z, 2));
    CurForward = _transform->GetLook();
    direction = PlayerPos - pos;
    direction.y += 1.f;
    direction.Normalize();

    if (distance < 0.5f)
    {
        CUR_SCENE->Remove(GetGameObject());
        OCTREE->RemoveCollider(GetGameObject()->GetCollider());
        return;
    }

    if (FirstTime_2)
    {

        Vec3 rotationAxis = CurForward.Cross(direction);

        rotationAxis.Normalize();

        // 각도 계산
        float angle = std::acos(CurForward.Dot(direction));

        // 방향에 따라 각도 조정 (y축 중심 회전)
        if (rotationAxis.y < 0) {
            angle = -angle;  // 왼쪽 회전
        }

        Vec3 newRotation = _transform->GetLocalRotation() + Vec3(0, angle, 0);
        _transform->SetRotation(newRotation);

        FirstTime = false;
        FirstTime_2 = false;
    }

    {
        pos += direction * speed * dt;
        _transform->SetPosition(pos);
    }
}
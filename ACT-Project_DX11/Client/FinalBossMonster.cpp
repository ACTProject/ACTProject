#include "pch.h"
#include "FinalBossMonster.h"

#define AttackRange 5.0f

void FinalBossMonster::SetAnimationState(AnimationState state)
{
    _modelAnimator->ChangeAnimation(state);
    _currentAnimationState = state;
}

void FinalBossMonster::Start()
{
    _transform = GetTransform();
    _player = SCENE->GetCurrentScene()->GetPlayer();
    SetAnimationState(AnimationState::Combat);
}

void FinalBossMonster::Update()
{
    if (INPUT->GetButton(KEY_TYPE::KEY_4))
    {
        int a = 0;
    }

    dt = TIME->GetDeltaTime();
    _FPS = static_cast<float>(TIME->GetFps());
    bossPos = _transform->GetPosition();
    playerPos = _player->GetTransform()->GetPosition();
    currentTime = TIME->GetGameTime(); // 현재 게임 시간

    if (myPhase == 1)
    {
        Phase_1();
    }
    else if (myPhase == 2)
    {
        Phase_2();
    }
}



void FinalBossMonster::Phase_1()
{
    if (isFirstTime) // 조우
    {
        if (currentTime > 10.f) // 실행되는데 걸리는 시간으로 인한 애니메이션이 짤리는 현상때문에 설정
        {
            //Rota(bossPos, playerPos);
            if (PlayCheckAnimating(AnimationState::Appear))
            {
                return;
            }
            isFirstTime = false;
            lastTime = currentTime;
        }
        else
        {
            return;
        }
    }

    if (currentTime - lastTime > 2.0f)
    {
        postpone = false;
    }

    if (!postpone)
    {
        Walk(bossPos, playerPos, 5.0f);
        Rota(bossPos, playerPos);

    }
}

void FinalBossMonster::Phase_2()
{

}

void FinalBossMonster::Appear()
{
}

void FinalBossMonster::Walk(Vec3 objPos, Vec3 targetPos, float speed)
{
    SetAnimationState(AnimationState::Walk);
    Vec3 direction = targetPos - objPos;
    if (direction.LengthSquared() < EPSILON) // EPSILON 사용
    {
        return;
    }

    direction.Normalize();  // 방향 벡터를 단위 벡터로 정규화

    _transform->SetPosition(_transform->GetPosition() + direction * speed * dt);  // 일정 거리만큼 이동
}

void FinalBossMonster::Rota(Vec3 objPos, Vec3 targetPos)
{
    Vec3 CurForward = _transform->GetLook();
    Vec3 direction = targetPos - objPos;
    direction.Normalize();

    // 외적을 이용한 회전 축 계산
    Vec3 rotationAxis = CurForward.Cross(direction);

    // 외적 결과가 매우 작으면 방향 차이가 거의 없으므로 회전 필요 없음
    if (rotationAxis.LengthSquared() < EPSILON)
    {
        return;
    }

    rotationAxis.Normalize();

    // 각도 계산
    float angle = std::acos(CurForward.Dot(direction));

    // 작은 각도는 무시
    if (abs(angle) < EPSILON) // 0.01 라디안(약 0.57도) 이하 회전 무시
    {
        return;
    }
    // 방향에 따라 각도 조정 (y축 중심 회전)
    if (rotationAxis.y < 0) {
        angle = -angle;  // 왼쪽 회전
    }

    // 현재 회전값 업데이트
    Vec3 currentRotation = _transform->GetLocalRotation();
    Vec3 newRotation = Vec3::Lerp(currentRotation, currentRotation + Vec3(0, angle, 0), 0.1f); // 0.1f는 보간 속도
    _transform->SetRotation(newRotation);
}


bool FinalBossMonster::PlayCheckAnimating(AnimationState state)
{
    SetAnimationState(state);

    animPlayingTime += dt;
    float duration = _enemy->GetAnimationDuration(static_cast<AnimationState>((int)state)) / _FPS;

    if (animPlayingTime >= duration)
    {
        animPlayingTime = 0.0f;
        SetAnimationState(AnimationState::Combat);
        return false;
    }

    return true;
}
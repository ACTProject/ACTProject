#pragma once
#include "MonoBehaviour.h"
#include "EnginePch.h"
#include "A_Star.h"
#include "Model.h"
#include "ModelAnimator.h"

class Model;
class ModelAnimator;

class FinalBossMonster : public MonoBehaviour
{
    virtual void Start() override;
    virtual void Update() override;

public:
    shared_ptr<Model> GetEnemy() { return _enemy; }
    void SetEnemy(shared_ptr<Model> enemy) { _enemy = enemy; }
    shared_ptr<ModelAnimator> GetModelAnimator() { return _modelAnimator; }
    void SetModelAnimator(shared_ptr<ModelAnimator> modelAnimator) { _modelAnimator = modelAnimator; }
    void SetAnimationState(AnimationState state);

    bool PlayCheckAnimating(AnimationState state);      // 해당 anim 플레이 , 플레이 중일시 true 아닐시 false
    void Phase_1();                                     // 1페이즈
    void Phase_2();                                     // 2페이즈
    void Appear();                                      // 조우시 모션용 어그로와 같음
    void Walk(Vec3 objPos, Vec3 targetPos, float speed);// 타겟 방향으로 이동
    void Rota(Vec3 objPos, Vec3 targetPos);             // 타겟 방향으로 회전
    void Die();                                         // 죽음
    bool Punch(int atkType);                            // 펀치 공격
    void Fireball();

    int comboCnt;
    int randType;                   //랜덤한 타입
    float currentTime = 0.f;            //현재 게임 시간
    float lastTime = 0.f;               //마지막 애니메이션 시간
    Vec3 bossPos;                       //보스 위치
    Vec3 playerPos;                     //플레이어 위치
    float distance;                     //플레이어 - 보스 거리
    Vec3 direction;                     //플레이어 - 보스 방향
    float animPlayingTime = 0.0f;       //애니메이션 플레이 타임
    int myPhase = 1;                    //1페이즈 2페이즈 구분용
    float hp = 1000.f;                  //보스 hp
    float _FPS;                         //게임 FPS = 60
    float dt;                           //deltaTime = 프레임당 시간
    bool isFirstTime = true;            //조우인지 여부 ( Appear 용 )
    bool postpone = false;              //패턴 끝나고 잠깐의 공백 시간


    bool chaseAble = false;             //추격
    bool punchAble = false;             //펀치 

private:
    shared_ptr<Model> _enemy;
    shared_ptr<ModelAnimator> _modelAnimator;
    shared_ptr<Transform> _transform;
    shared_ptr<GameObject> _player;
    AnimationState _currentAnimationState = AnimationState::Idle;
};


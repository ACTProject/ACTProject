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

    bool PlayCheckAnimating(AnimationState state);
    void Phase_1();
    void Phase_2();
    void Appear();
    void Walk(Vec3 objPos, Vec3 targetPos, float speed);
    void Rota(Vec3 objPos, Vec3 targetPos);

    float currentTime = 0.f;
    float lastTime = 0.f;
    Vec3 bossPos;
    Vec3 playerPos;
    float animPlayingTime = 0.0f;
    int myPhase = 1;
    float hp = 1000.f;
    float _FPS;
    float dt;
    bool isAnimating = false;
    bool isFirstTime = true;
    bool postpone = false;

private:
    shared_ptr<Model> _enemy;
    shared_ptr<ModelAnimator> _modelAnimator;
    shared_ptr<Transform> _transform;
    shared_ptr<GameObject> _player;
    AnimationState _currentAnimationState = AnimationState::Combat;
};


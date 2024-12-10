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


private:
    shared_ptr<Model> _enemy;
    shared_ptr<ModelAnimator> _modelAnimator;
    shared_ptr<Transform> _transform;
    shared_ptr<GameObject> _player;
    AnimationState _currentAnimationState = AnimationState::Idle;
};


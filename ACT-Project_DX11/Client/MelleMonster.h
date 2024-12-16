#pragma once
#include "MonoBehaviour.h"
#include "EnginePch.h"
#include "A_Star.h"
#include "Model.h"
#include "ModelAnimator.h"

class Model;
class ModelAnimator;

class MelleMonster : public MonoBehaviour
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
    void Aggro();
    void Move(Vec3 objPos, Vec3 targetPos, float speed);
    void Rota(Vec3 objPos, Vec3 targetPos);
    void Attack(int type);
    void Tracking(Vec3 pos, const std::vector<Node3D>& path);
    void ResetToIdleState();
    void Patrol(Vec3 Target);

	float _speed = 10.f;
	float _hp = 100.0f;
	float _atk = 30.0f;
	float dt;
	float _FPS;
	float rangeDis;
	float _attackDuration[3];
	float _aggroDuration;
	float animPlayingTime = 0.0f;
    float distance;
    int atkType = 1;

	bool hasPatrolTarget = false;
    bool onTarget = false;
    bool onRange = false;
    bool BackToStart = false;
    bool isFirstAggro = true;
    bool onAttack = false;
    bool _isAnimating = false;

    // 히트 상태
    bool _hit = false;

    Vec3 StartPos;
    Vec3 CurForward;
    Vec3 EnemyPos;
    Vec3 PlayerPos;
    Vec3 patrolTarget;

	shared_ptr<Model> _enemy;
	shared_ptr<ModelAnimator> _modelAnimator;
	shared_ptr<Transform> _transform;
	shared_ptr<GameObject> _player;
	AnimationState _currentAnimationState = AnimationState::Idle;
};


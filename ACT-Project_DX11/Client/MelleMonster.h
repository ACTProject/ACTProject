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

	void Aggro();
	void Move(Vec3 objPos, Vec3 targetPos, float speed);
	void Rota(Vec3 objPos, Vec3 targetPos);
	void Attack(int type);
	void Tracking(Vec3 pos, const std::vector<Node3D>& path);
	void ResetToIdleState();
	void Patrol();

	//float angle; 
	float distance;
	Vec3 CurForward;
	Vec3 EnemyPos;
	Vec3 PlayerPos;
	Vec3 patrolTarget;
	int atkType = 1;
	bool _isAnimating = false;

private:
	float _speed = 10.f;
	float _hp = 100.0f;
	float _atk = 30.0f;
	bool onTarget = false;
	bool onRange = false;
	bool BackToStart = false;
	float dt;
	float _FPS;
	Vec3 StartPos;
	float rangeDis;
	bool onAttack = false;
	float _attackDuration[3];
	float _aggroDuration;
	bool isFirstAggro = true;
	float animPlayingTime = 0.0f;
	bool hasPatrolTarget = false;

	shared_ptr<Model> _enemy;
	shared_ptr<ModelAnimator> _modelAnimator;
	shared_ptr<Transform> _transform;
	shared_ptr<GameObject> _player;
	AnimationState _currentAnimationState = AnimationState::Idle;
};


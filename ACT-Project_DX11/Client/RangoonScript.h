#pragma once
#include "MonoBehaviour.h"
#include "EnginePch.h"
#include "A_Star.h"
#include "Model.h"
#include "ModelAnimator.h"

class Model;
class ModelAnimator;

class RangoonScript : public MonoBehaviour
{
	A_Star astar;
	virtual void Start() override;
	virtual void Update() override;

public:
	shared_ptr<Model> GetEnemy() { return _rangoon; }
	void SetEnemy(shared_ptr<Model> enemy) { _rangoon = enemy; }
	shared_ptr<ModelAnimator> GetModelAnimator() { return _modelAnimator; }
	void SetModelAnimator(shared_ptr<ModelAnimator> modelAnimator) { _modelAnimator = modelAnimator; }
	void SetAnimationState(AnimationState state);

	void Aggro();
	void Move(const Vec3 targetPos);
	void Rota(const Vec3 targetPos);
	void Attack(int type);
	void Tracking(Vec3 pos, const std::vector<Node3D>& path);
	void SetNextType(int type);
	void ResetToIdleState();

	void UpdateTimers();
	void UpdatePlayerInfo();
	void CheckRanges();
	void HandleAnimationState();
	void HandleBackToStart();
	void HandleChasePlayer();
	void HandleAttack();

	//float angle; 
	float distance;
	Vec3 direction;
	Vec3 CurForward;
	int atkType = 1;
	bool _isAnimating = false;

private:
	float _speed = 0.1f;
	float _deltaTime = 1.f;
	float _hp = 100.0f;
	float _atk = 30.0f;
	bool onTarget = false;
	bool onRange = true;
	bool BackToStart = false;
	float _FPS;
	Vec3 StartPos;
	float rangeDis;
	bool onAttack = false;
	float _attackDuration[3];
	float _aggroDuration;
	bool isAggro = false;
	float animPlayingTime = 0.0f;

	shared_ptr<Model> _rangoon;
	shared_ptr<ModelAnimator> _modelAnimator;
	shared_ptr<Transform> _transform;
	shared_ptr<GameObject> _player;
	AnimationState _currentAnimationState = AnimationState::Idle;
};


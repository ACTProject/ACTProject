#pragma once
#include "MonoBehaviour.h"
#include "Camera.h"

class Model;
class ModelAnimator;

class PlayerScript : public MonoBehaviour
{
	virtual void Start() override;
	virtual void Update() override;

public:
	shared_ptr<Model> GetPlayer() { return _player; }
	void SetPlayer(shared_ptr<Model> player) { _player = player; }	
	shared_ptr<ModelAnimator> GetModelAnimator() { return _modelAnimator; }
	void SetModelAnimator(shared_ptr<ModelAnimator> modelAnimator) { _modelAnimator = modelAnimator; }
	void SetAnimationState(AnimationState state);
	void SetHitBox(shared_ptr<GameObject> hitbox) { _hitbox = hitbox; }
	void SetCamera(shared_ptr<GameObject> camera) { _camera = camera; }

	void StartAttack();
	void ContinueAttack();
	void PlayAttackAnimation(int stage);
    void Rota(Vec3 objPos, Vec3 targetPos);
	void ResetToIdleState();
private:
	float _speed = 5.f;
	shared_ptr<Model> _player;
	shared_ptr<ModelAnimator> _modelAnimator;
	shared_ptr<Transform> _transform;
    shared_ptr<GameObject> _camera;
	shared_ptr<GameObject> _hitbox;

private:
	float _FPS;

	// Attack
	int _attackStage = 0; // 현재 공격 단계 (0: Idle, 1~4: 연속 공격 단계)
	bool _isAttacking = false; // 공격 중인지 여부
	float _attackCooldown = 0.f; // 공격 애니메이션 최소 실행 시간
	float _attackTimer = 0.0f; // 현재 공격 단계의 경과 시간

	float _attackDurations[4]; // 각 공격 애니메이션 지속 시간 (초)
	float _currentDuration = 0.f;

    Vec3 CurForward;

	bool _isPlayeringAttackAnimation = false; // 공격 애니메이션 재생 중인지 여부 확인
	AnimationState _currentAnimationState = AnimationState::Idle;
};


#pragma once
#include "MonoBehaviour.h"

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
	void ResetAnimationState();
private:
	float _speed = 5.f;
	shared_ptr<Model> _player;
	shared_ptr<ModelAnimator> _modelAnimator;
	shared_ptr<Transform> _transform;

public:
	bool _isPlayeringAttackAnimation = false; // 공격 애니메이션 재생 중인지 여부 확인
	AnimationState _currentAnimationState = AnimationState::Idle;
};


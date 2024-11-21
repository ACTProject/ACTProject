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

	void Aggro(Vec3& s, Vec3& t);
	void Move(const Vec3& targetPos);
	void Attack();
	void Tracking(Vec3 pos, const std::vector<Node3D>& path);

private:
	float _speed = 1.f;
	float _deltaTime = 0.1f;
	shared_ptr<Model> _rangoon;
	shared_ptr<ModelAnimator> _modelAnimator;
	shared_ptr<Transform> _transform;
};


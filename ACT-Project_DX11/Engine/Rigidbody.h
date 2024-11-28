#pragma once
#include "Component.h"
class Rigidbody : public Component
{
public:
	Rigidbody();
	virtual ~Rigidbody();

	virtual void Start() override;
	virtual void FixedUpdate() override;

	void Addforce(const Vec3& force);
	void ApplyFriction();
	void HandleCollisionWithTerrain(Vec3& objectPosition);
	const Vec3 GetVelocity() { return _velocity; }
	void SetVelocity(Vec3 velocity) { _velocity = velocity; }
	const float GetMass() { return _mass; }
	void SetMass(float mass) { _mass = mass; }

	bool GetUseGravity() { return _useGravity; }
	void SetUseGravity(bool useGravity) { _useGravity = useGravity; }
private:
	Vec3 _velocity = Vec3(0.f);		// 속도
	Vec3 _force = Vec3(0.f);		// 외부 힘
	float _mass = 1.0f;				// 질량
	bool _useGravity = false;		// 중력 사용 여부

	float _fixedDeltaTime = 0.f;
};


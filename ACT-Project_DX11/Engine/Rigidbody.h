#pragma once
#include "Component.h"
class Rigidbody : public Component
{
public:
	Rigidbody();
	virtual ~Rigidbody();

	void Addforce(const Vec3& force);

	void SetMass(float mass) { _mass = mass; }
	const float GetMass() { return _mass; }
private:
	Vec3 _velocity;		// 속도
	Vec3 _force;		// 외부 힘
	float _mass;		// 질량
	bool _useGravity	// 중력 사용 여부
};


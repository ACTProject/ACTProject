#include "pch.h"
#include "Rigidbody.h"
#include "Terrain.h"

Rigidbody::Rigidbody() : Component(ComponentType::Rigidbody)
{

}

Rigidbody::~Rigidbody()
{
}

void Rigidbody::Start()
{
	_fixedDeltaTime = SCENE->GetFixedDeltaTime();
}

void Rigidbody::FixedUpdate()
{
	shared_ptr<Transform> transform = GetTransform();
	if (_fixedDeltaTime == 0.f)
		return;

	// 중력 적용
	if (_useGravity)
		Addforce(Vec3(0, -9.8f * _mass, 0)); // F = m * g

	// 가속도 계산 (a = F / m)
	Vec3 acceleration = _force / _mass;

	// 속도 계산 (v = v0 + at)
	_velocity += acceleration * _fixedDeltaTime;

	// 위치 계산 (s = s0 + vt)
	//shared_ptr<Transform> transform = GetTransform();
	if (transform != nullptr)
	{
		Vec3 position = transform->GetPosition();
		HandleCollisionWithTerrain(position);
		position += _velocity * _fixedDeltaTime;
		transform->SetPosition(position);
	}

	// 외부 힘 초기화
	_force = Vec3(0.f);
}

void Rigidbody::Addforce(const Vec3& force)
{
	_force += force;
}

void Rigidbody::HandleCollisionWithTerrain(Vec3& objectPosition)
{
	auto terrain = SCENE->GetCurrentScene()->GetCurrentTerrain();
	// Terrain의 해당 위치에서 높이 가져오기
	float terrainHeight = terrain->GetTerrain()->GetHeightAtPosition(objectPosition.x, objectPosition.z);

	Vec3 tp = terrain->GetTransform()->GetPosition();
	Vec3 player = GetTransform()->GetPosition();

	// 물체가 Terrain 아래로 내려가면 충돌 처리
	if (objectPosition.y <= terrainHeight) {
		objectPosition.y = terrainHeight;  // Terrain 위로 위치 조정
		_velocity.y = 0.0f;          // y축 속도 제거
	}
}

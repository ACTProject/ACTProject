#include "pch.h"
#include "CollisionManager.h"
#include "BaseCollider.h"
#include "Rigidbody.h"

void CollisionManager::Init()
{

}

// 충돌 감지 및 처리
void CollisionManager::Update()
{
	for (size_t i = 0; i < _colliders.size(); ++i)
	{
		for (size_t j = i + 1; j < _colliders.size(); ++j)
		{
			auto colliderA = _colliders[i];
			auto colliderB = _colliders[j];

			// 충돌 감지
			if (colliderA->Intersects(colliderB))
			{
				HandleCollision(colliderA, colliderB);
			}
		}
	}
}

void CollisionManager::AddCollider(shared_ptr<BaseCollider> collider)
{
	if (collider)
		_colliders.push_back(collider);
}

void CollisionManager::AddRigidbody(shared_ptr<Rigidbody> rigidbody)
{
	if (rigidbody)
		_rigidbodies.push_back(rigidbody);
}

void CollisionManager::HandleCollision(shared_ptr<BaseCollider> colliderA, shared_ptr<BaseCollider> colliderB)
{
	auto rigidbodyA = colliderA->GetGameObject()->GetRigidbody();
	auto rigidbodyB = colliderB->GetGameObject()->GetRigidbody();

	if (!rigidbodyA || !rigidbodyB)
		return;

	// 두 Collider가 충돌 중인지 확인
	if (!colliderA->IsColliding() && )
	// 질량 비교에 따라 충돌 처리
	if (rigidbodyA->GetMass() > rigidbodyB->GetMass())
	{
		ApplyForce(rigidbodyB, colliderB->GetColliderCenter(), colliderA->GetColliderCenter()
			, rigidbodyA->GetMass() - rigidbodyB->GetMass());
	}
	else if (rigidbodyA->GetMass() < rigidbodyB->GetMass())
	{
		ApplyForce(rigidbodyA, colliderA->GetColliderCenter(), colliderB->GetColliderCenter()
			, rigidbodyB->GetMass() - rigidbodyA->GetMass());
	}
}

void CollisionManager::ApplyForce(shared_ptr<Rigidbody> rigidbody, const Vec3& target, const Vec3& source, float massDifference)
{
	Vec3 collisionNormal = target - source;
	collisionNormal.Normalize();

	Vec3 force = collisionNormal * massDifference * 10.0f; // 밀림 강도
	rigidbody->Addforce(force);
}

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

			// Collider가 비활성화 상태이면 충돌 검사 중단
			if (!colliderA->IsActive() || !colliderB->IsActive())
				continue;

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
	// Rigidbody 가져오기
	auto rigidbodyA = colliderA->GetGameObject()->GetRigidbody();
	auto rigidbodyB = colliderB->GetGameObject()->GetRigidbody();

	// Rigidbody가 없으면 처리하지 않음
	if (!rigidbodyA || !rigidbodyB)
		return;

	// Penetration Depth 계산
	Vec3 penetrationDepth;
	if (!colliderA->CalculatePenetraionDepth(colliderB, penetrationDepth))
	{
		return; // 충돌이 발생하지 않음
	}

	// 충돌 방향 계산
	penetrationDepth.Normalize();
	Vec3 collisionNormal = penetrationDepth;

	// 간격 유지 설정
	float minimumSeparation = 0.1f; // 오브젝트 간 최소 간격
	float penetrationLength = penetrationDepth.Length();

	if (penetrationLength <= minimumSeparation)
	{
		// 이미 충분한 거리가 유지되면 더 이상 밀어내지 않음
		return;
	}

	// 질량 확인
	float massA = rigidbodyA->GetMass();
	float massB = rigidbodyB->GetMass();

	if (massA > massB)
	{
		ApplyForce(rigidbodyB, colliderB->GetColliderCenter(), colliderA->GetColliderCenter(), rigidbodyA->GetMass() - rigidbodyB->GetMass());
	}
	else
	{
		ApplyForce(rigidbodyA, colliderA->GetColliderCenter(), colliderB->GetColliderCenter(), rigidbodyB->GetMass() - rigidbodyA->GetMass());
	}

	// 충돌 상태 설정
	colliderA->SetColliding(true);
	colliderB->SetColliding(true);
}

void CollisionManager::ApplyForce(shared_ptr<Rigidbody> rigidbody, const Vec3& target, const Vec3& source, float massDifference)
{
	Vec3 collisionNormal = (target - source);
	collisionNormal.Normalize();
	Vec3 force = collisionNormal * massDifference * 10.0f; // 밀림 강도
	rigidbody->Addforce(force);
}

void CollisionManager::Remove(shared_ptr<GameObject> obj)
{
	auto it = std::find(_colliders.begin(),_colliders.end(),obj->GetCollider());
	if (it != _colliders.end())
	{
		_colliders.erase(it);
	}

	auto its = std::find(_rigidbodies.begin(), _rigidbodies.end(), obj->GetRigidbody());
	if (its != _rigidbodies.end())
	{
		_rigidbodies.erase(its);
	}
vector<shared_ptr<BaseCollider>> CollisionManager::GetNearbyTargets(const Vec3& playerPosition, float radius)
{
	vector<shared_ptr<BaseCollider>> nearbyTargets;
	for (const auto& collider : _colliders)
	{
		Vec3 colliderCenter = collider->GetColliderCenter();
		float distance = (colliderCenter - playerPosition).Length();

		if (distance <= radius)
		{
			nearbyTargets.push_back(collider);
		}
	}
	return nearbyTargets;
}


#include "pch.h"
#include "CollisionManager.h"
#include "BaseCollider.h"
#include "Rigidbody.h"

void CollisionManager::Init()
{

}

// 異⑸룎 媛먯? 諛?泥섎━
void CollisionManager::Update()
{
	for (size_t i = 0; i < _colliders.size(); ++i)
	{
		for (size_t j = i + 1; j < _colliders.size(); ++j)
		{
			auto colliderA = _colliders[i];
			auto colliderB = _colliders[j];

			// Collider媛 鍮꾪솢?깊솕 ?곹깭?대㈃ 異⑸룎 寃??以묐떒
			if (!colliderA->IsActive() || !colliderB->IsActive())
				continue;

			// 異⑸룎 媛먯?
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
	// Rigidbody 媛?몄삤湲?
	auto rigidbodyA = colliderA->GetGameObject()->GetRigidbody();
	auto rigidbodyB = colliderB->GetGameObject()->GetRigidbody();

	// Rigidbody媛 ?놁쑝硫?泥섎━?섏? ?딆쓬
	if (!rigidbodyA || !rigidbodyB)
		return;

	// Penetration Depth 怨꾩궛
	Vec3 penetrationDepth;
	if (!colliderA->CalculatePenetraionDepth(colliderB, penetrationDepth))
	{
		return; // 異⑸룎??諛쒖깮?섏? ?딆쓬
	}

	// 異⑸룎 諛⑺뼢 怨꾩궛
	penetrationDepth.Normalize();
	Vec3 collisionNormal = penetrationDepth;

	// 媛꾧꺽 ?좎? ?ㅼ젙
	float minimumSeparation = 0.1f; // ?ㅻ툕?앺듃 媛?理쒖냼 媛꾧꺽
	float penetrationLength = penetrationDepth.Length();

	if (penetrationLength <= minimumSeparation)
	{
		// ?대? 異⑸텇??嫄곕━媛 ?좎??섎㈃ ???댁긽 諛?대궡吏 ?딆쓬
		return;
	}

	// 吏덈웾 ?뺤씤
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

	// 異⑸룎 ?곹깭 ?ㅼ젙
	colliderA->SetColliding(true);
	colliderB->SetColliding(true);
}

void CollisionManager::ApplyForce(shared_ptr<Rigidbody> rigidbody, const Vec3& target, const Vec3& source, float massDifference)
{
	Vec3 collisionNormal = (target - source);
	collisionNormal.Normalize();
	Vec3 force = collisionNormal * massDifference * 10.0f; // 諛由?媛뺣룄
	rigidbody->Addforce(force);
}

void CollisionManager::Remove(shared_ptr<GameObject> obj)
{
    auto it = std::find(_colliders.begin(), _colliders.end(), obj->GetCollider());
    if (it != _colliders.end())
    {
        _colliders.erase(it);
    }

    auto its = std::find(_rigidbodies.begin(), _rigidbodies.end(), obj->GetRigidbody());
    if (its != _rigidbodies.end())
    {
        _rigidbodies.erase(its);
    }
}


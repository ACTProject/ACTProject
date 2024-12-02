#include "pch.h"
#include "HitBox.h"
#include "AABBBoxCollider.h"

HitBox::HitBox() : Super(ComponentType::HitBox)
{

}

HitBox::~HitBox()
{

}

void HitBox::Craete(shared_ptr<GameObject> player)
{
	auto go = _gameObject.lock();
	if (!go) return;

	// 플레이어 위치를 기준으로 히트박스 위치 설정
	Vec3 playerPosition = player->GetTransform()->GetPosition();
	go->GetOrAddTransform()->SetPosition(playerPosition + _offset);

	// Collider
	auto collider = make_shared<AABBBoxCollider>();
	collider->SetRadius(5.0f);
	collider->SetOffset(Vec3(0.f, 1.f, 0.f));
	player->AddComponent(collider);
}

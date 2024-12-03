#include "pch.h"
#include "HitBox.h"
#include "AABBBoxCollider.h"

HitBox::HitBox() : Super(ComponentType::HitBox)
{

}

HitBox::~HitBox()
{

}

void HitBox::Craete(shared_ptr<GameObject> target, Vec3 size)
{
	auto go = _gameObject.lock();
	if (!go) return;

	// 플레이어 위치를 기준으로 히트박스 위치 설정
	auto targetTransform = target->GetTransform();
	go->GetOrAddTransform()->SetPosition(targetTransform->GetPosition() +_offset + targetTransform->GetLook() * 1.8f);

	// Collider
	auto collider = make_shared<AABBBoxCollider>();
	collider->GetBoundingBox().Extents = size;
	collider->SetOffset(Vec3(0.f, 1.f, 0.f));
	go->AddComponent(collider);
}

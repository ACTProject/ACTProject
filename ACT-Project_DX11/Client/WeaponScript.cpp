#include "pch.h"
#include "WeaponScript.h"
#include "ModelMesh.h"
#include "Model.h"
#include "Transform.h"

void WeaponScript::Update()
{
	AttachWeaponToHand();
}

void WeaponScript::Start()
{
	
}

void WeaponScript::AttachWeaponToHand()
{
	//_transform = GetTransform();
	//// 무기를 장착할 손
	//shared_ptr<ModelBone> handBone = _player->GetBoneByName(L"Hand_Grip_L");

	//Matrix handBoneMatrix = handBone->transform;	// 본 행렬
	//Vec3 handPosition = handBoneMatrix.Translation();	// 손 위치
	//Quaternion handQuaternion = Quaternion::CreateFromRotationMatrix(handBoneMatrix);
	//Vec3 handRotation = Transform::ToEulerAngles(handQuaternion); // 손 회전

	//_transform->SetPosition(handPosition);
	//_transform->SetRotation(handRotation);
}

#include "pch.h"
#include "EnemyManager.h"

void EnemyManager::CreateMeleeMonster(Vec3 SpawnPos)
{
    auto rangoon = make_shared<GameObject>();
    {
        rangoon->SetObjectType(ObjectType::Monster);
        rangoon->GetOrAddTransform()->SetPosition(SpawnPos);
        rangoon->GetOrAddTransform()->SetLocalRotation(Vec3(0, 0, 0)); // XMConvertToRadians()
        rangoon->GetOrAddTransform()->SetScale(Vec3(0.0001f));

        shared_ptr<Model> enemyModel = make_shared<Model>();
        // Model
        {
            enemyModel->ReadModel(L"Enemy/Rangoon");
            enemyModel->ReadMaterial(L"Enemy/Rangoon");

            enemyModel->ReadAnimation(L"Enemy/Rangoon_idle", AnimationState::Idle);
            enemyModel->ReadAnimation(L"Enemy/Rangoon_run", AnimationState::Run);
            enemyModel->ReadAnimation(L"Enemy/Rangoon_aggro", AnimationState::Aggro);
            enemyModel->ReadAnimation(L"Enemy/Rangoon_atkBigSnippy", AnimationState::Attack1);
            enemyModel->ReadAnimation(L"Enemy/Rangoon_atkSmallSnippy", AnimationState::Attack2);
            enemyModel->ReadAnimation(L"Enemy/Rangoon_atkSmash", AnimationState::Attack3);
            enemyModel->ReadAnimation(L"Enemy/Rangoon_die", AnimationState::Die);
            enemyModel->ReadAnimation(L"Enemy/Rangoon_hit", AnimationState::Hit);
            enemyModel->ReadAnimation(L"Enemy/Rangoon_roar", AnimationState::Roar);
        }
        shared_ptr<ModelAnimator> ma2 = make_shared<ModelAnimator>(renderShader);
        rangoon->AddComponent(ma2);
        {
            rangoon->GetModelAnimator()->SetModel(enemyModel);
            rangoon->GetModelAnimator()->SetPass(2);
        }
        shared_ptr<MelleMonster> rangoonScript = make_shared<MelleMonster>();

        rangoonScript->SetEnemy(enemyModel);
        rangoonScript->SetModelAnimator(ma2);

        rangoon->SetController(rangoonScript);
        rangoon->AddComponent(rangoonScript);

        // Collider
        auto collider = make_shared<AABBBoxCollider>();
        collider->SetBoundingBox(BoundingBox(Vec3(0.f), Vec3(1.5f)));
        collider->SetOffset(Vec3(0.f, 1.f, 0.f));
        OCTREE->InsertCollider(collider);
        rangoon->AddComponent(collider);

        // Rigidbody
        shared_ptr<Rigidbody> rigidBody = make_shared<Rigidbody>();
        rigidBody->SetUseGravity(true);
        rigidBody->SetMass(2.0f + (rand() % 10 * 0.1));
        rangoon->AddComponent(rigidBody);

        COLLISION->AddRigidbody(rigidBody);
        COLLISION->AddCollider(collider);

        CUR_SCENE->Add(rangoon);
    }
}

void EnemyManager::CreateShootingMonster(Vec3 SpawnPos)
{
    auto PistolShrimp = make_shared<GameObject>(); // Pistol_Shrimp
    {
        PistolShrimp->SetObjectType(ObjectType::Monster);
        PistolShrimp->GetOrAddTransform()->SetPosition(SpawnPos);
        PistolShrimp->GetOrAddTransform()->SetLocalRotation(Vec3(0, XMConvertToRadians(180), 0)); // XMConvertToRadians()
        PistolShrimp->GetOrAddTransform()->SetScale(Vec3(0.01f));
        //Vec3(XMConvertToRadians(90), 0, XMConvertToRadians(90))
        shared_ptr<Model> enemyModel = make_shared<Model>();
        // Model
        {
            enemyModel->ReadModel(L"Enemy/pistol");
            enemyModel->ReadMaterial(L"Enemy/pistol");

            enemyModel->ReadAnimation(L"Enemy/pistol_Idle", AnimationState::Idle);
            enemyModel->ReadAnimation(L"Enemy/pistol_shoot", AnimationState::Attack1);
            enemyModel->ReadAnimation(L"Enemy/pistol_aggro", AnimationState::Aggro);

        }
        shared_ptr<ModelAnimator> ma2 = make_shared<ModelAnimator>(renderShader);
        PistolShrimp->AddComponent(ma2);
        {
            PistolShrimp->GetModelAnimator()->SetModel(enemyModel);
            PistolShrimp->GetModelAnimator()->SetPass(2);
        }
        shared_ptr<ShootingMonster> ShrimpScript = make_shared<ShootingMonster>();

        ShrimpScript->SetEnemy(enemyModel);
        ShrimpScript->SetModelAnimator(ma2);

        PistolShrimp->SetController(ShrimpScript);
        PistolShrimp->AddComponent(ShrimpScript);

        // Collider
        auto collider = make_shared<AABBBoxCollider>();
        collider->SetBoundingBox(BoundingBox(Vec3(0.f), Vec3(1.5f)));
        collider->SetOffset(Vec3(0.f, 1.f, 0.f));
        OCTREE->InsertCollider(collider);
        PistolShrimp->AddComponent(collider);

        // Rigidbody
        shared_ptr<Rigidbody> rigidBody = make_shared<Rigidbody>();
        rigidBody->SetUseGravity(true);
        rigidBody->SetMass(2.1f);
        PistolShrimp->AddComponent(rigidBody);

        COLLISION->AddRigidbody(rigidBody);
        COLLISION->AddCollider(collider);

        CUR_SCENE->Add(PistolShrimp);
    }
}

#include "pch.h"
#include "EnemyManager.h"

void EnemyManager::CreateMeleeMonster(Vec3 SpawnPos)
{
    auto rangoon = make_shared<GameObject>();
    {
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
            enemyModel->ReadAnimation(L"Enemy/Rangoon_hit", AnimationState::Hit1);
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

void EnemyManager::CreateFinalBoss(Vec3 SpawnPos)
{
    auto FinalBoss = make_shared<GameObject>(); // Pistol_Shrimp
    {
        FinalBoss->GetOrAddTransform()->SetPosition(SpawnPos);
        FinalBoss->GetOrAddTransform()->SetLocalRotation(Vec3(0, XMConvertToRadians(180), 0)); // XMConvertToRadians()
        FinalBoss->GetOrAddTransform()->SetScale(Vec3(0.001f));

        shared_ptr<Model> enemyModel = make_shared<Model>();
        // Model
        {
            enemyModel->ReadModel(L"Enemy/FinalBoss/mrKrab");
            enemyModel->ReadMaterial(L"Enemy/FinalBoss/mrKrab");

            enemyModel->ReadAnimation(L"Enemy/FinalBoss/mrKRAB_idle", AnimationState::Idle);
            enemyModel->ReadAnimation(L"Enemy/FinalBoss/back_sprint", AnimationState::Run3);
            enemyModel->ReadAnimation(L"Enemy/FinalBoss/boxing_1", AnimationState::Attack1);
            enemyModel->ReadAnimation(L"Enemy/FinalBoss/boxing_2", AnimationState::Attack2);
            enemyModel->ReadAnimation(L"Enemy/FinalBoss/boxing_3", AnimationState::Attack3);
            enemyModel->ReadAnimation(L"Enemy/FinalBoss/boxing_4", AnimationState::Attack4);
            enemyModel->ReadAnimation(L"Enemy/FinalBoss/choke_lift", AnimationState::Skill1);
            enemyModel->ReadAnimation(L"Enemy/FinalBoss/dying", AnimationState::Die);
            enemyModel->ReadAnimation(L"Enemy/FinalBoss/fight_idle", AnimationState::Combat);
            enemyModel->ReadAnimation(L"Enemy/FinalBoss/fireball", AnimationState::Skill2);
            enemyModel->ReadAnimation(L"Enemy/FinalBoss/getUp_behind", AnimationState::GetUP1);
            enemyModel->ReadAnimation(L"Enemy/FinalBoss/getUp_front", AnimationState::GetUP2);
            enemyModel->ReadAnimation(L"Enemy/FinalBoss/hit_1", AnimationState::Hit1);
            enemyModel->ReadAnimation(L"Enemy/FinalBoss/hit_2", AnimationState::Hit2);
            enemyModel->ReadAnimation(L"Enemy/FinalBoss/jumping", AnimationState::Jump);
            enemyModel->ReadAnimation(L"Enemy/FinalBoss/magic_spell", AnimationState::Skill3);
            enemyModel->ReadAnimation(L"Enemy/FinalBoss/run_forward", AnimationState::Run);
            enemyModel->ReadAnimation(L"Enemy/FinalBoss/sprint", AnimationState::Run2);
            enemyModel->ReadAnimation(L"Enemy/FinalBoss/sweep", AnimationState::Skill4);
            enemyModel->ReadAnimation(L"Enemy/FinalBoss/thrust_slash", AnimationState::Skill5);
            enemyModel->ReadAnimation(L"Enemy/FinalBoss/uppercut", AnimationState::Skill6);
            enemyModel->ReadAnimation(L"Enemy/FinalBoss/warming_up", AnimationState::Skill7);
            enemyModel->ReadAnimation(L"Enemy/FinalBoss/super/super_GettingThrown", AnimationState::Skill8);
            enemyModel->ReadAnimation(L"Enemy/FinalBoss/super/super_GrabSlam", AnimationState::Skill9);
            enemyModel->ReadAnimation(L"Enemy/FinalBoss/super/super_Hurricane", AnimationState::Skill10);

        }
        shared_ptr<ModelAnimator> ma2 = make_shared<ModelAnimator>(renderShader);
        FinalBoss->AddComponent(ma2);
        {
            FinalBoss->GetModelAnimator()->SetModel(enemyModel);
            FinalBoss->GetModelAnimator()->SetPass(2);
        }
        shared_ptr<FinalBossMonster> BossScript = make_shared<FinalBossMonster>();

        BossScript->SetEnemy(enemyModel);
        BossScript->SetModelAnimator(ma2);

        FinalBoss->AddComponent(BossScript);

        // Collider
        auto collider = make_shared<AABBBoxCollider>();
        collider->SetBoundingBox(BoundingBox(Vec3(0.f), Vec3(1.5f)));
        collider->SetOffset(Vec3(0.f, 1.f, 0.f));
        OCTREE->InsertCollider(collider);
        FinalBoss->AddComponent(collider);

        // Rigidbody
        shared_ptr<Rigidbody> rigidBody = make_shared<Rigidbody>();
        rigidBody->SetUseGravity(true);
        rigidBody->SetMass(2.1f);
        FinalBoss->AddComponent(rigidBody);

        COLLISION->AddRigidbody(rigidBody);
        COLLISION->AddCollider(collider);

        CUR_SCENE->Add(FinalBoss);
    }
}

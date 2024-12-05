#pragma once
#include "ShootingMonster.h"
#include "MelleMonster.h"
#include "Rigidbody.h"
#include "AABBBoxCollider.h"

class EnemyManager
{
    shared_ptr<Shader> renderShader = make_shared<Shader>(L"23. RenderDemo.fx");

public:
    void CreateMeleeMonster(Vec3 SpawnPos);
    void CreateShootingMonster(Vec3 SpawnPos);

    Vec3 Spawnpos;
};

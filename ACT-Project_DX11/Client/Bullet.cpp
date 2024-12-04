#include "pch.h"
#include "Bullet.h"

void Bullet::Init(Vec3 Pos, Vec3 dir)
{
    auto bullet = make_shared<GameObject>(); // bullet
    
    bullet->GetOrAddTransform()->SetPosition({ Pos.x, Pos.y + 2.f, Pos.z });
    bullet->GetOrAddTransform()->SetLocalRotation(dir); // XMConvertToRadians()
    bullet->GetOrAddTransform()->SetScale(Vec3(0.0001f));

    shared_ptr<Model> objModel = make_shared<Model>();
    // Model
    objModel->ReadModel(L"Enemy/bullet");
    objModel->ReadMaterial(L"Enemy/bullet");
    
    shared_ptr<ModelAnimator> ma2 = make_shared<ModelAnimator>(renderShader);
    bullet->AddComponent(ma2);
    bullet->GetModelAnimator()->SetModel(objModel);
    bullet->GetModelAnimator()->SetPass(0);

    shared_ptr<Bullet> BulletScript = make_shared<Bullet>();

    BulletScript->SetObject(objModel);

    bullet->AddComponent(BulletScript);
    CUR_SCENE->Add(bullet);
    
    //bulletList.emplace_back(bullet);
    
    direction = dir;
    StartPos = Pos;
}

void Bullet::Start()
{
    
}

void Bullet::Update()
{
    if (!bulletList.empty())
    {
        for (auto bullet : bulletList)
        {
            float dt = TIME->GetDeltaTime();
            Vec3 pos = bullet.GetTransform()->GetPosition();
            float distance = Vec3::Distance(pos, StartPos);

            if (distance > 25.f)
            {
                Delete();
                return;
            }
            else
            {
                direction.Normalize();
                _transform->SetPosition(_transform->GetPosition() + direction * speed * dt);
            }

        }
    }
    int k = 0;
}

void Bullet::Delete()
{
}

#pragma once
#include "Model.h"
#include "GameObject.h"
#include "ModelAnimator.h"
#include "EnginePch.h"
#include "MonoBehaviour.h"

class BulletScript : public MonoBehaviour
{
    virtual void Start() override;
    virtual void Update() override;

public:
    shared_ptr<Model> GetObjects () { return _bullet; }
    void Add(shared_ptr<Model> bullet) { _bullet = bullet; }

    void Shooting();

    Vec3 direction;   // 총알 이동 방향
    Vec3 CurForward;
    float speed = 50.f;      // 총알 속도
    Vec3 PlayerPos;
    bool FirstTime = true;
    bool FirstTime_2 = true;
    shared_ptr<Model> _bullet;

private:
    shared_ptr<Transform> _transform;
    shared_ptr<GameObject> _player;
};


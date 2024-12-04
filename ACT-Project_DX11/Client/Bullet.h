#pragma once
#include "Model.h"
#include "GameObject.h"
#include "ModelAnimator.h"
#include "EnginePch.h"
#include "MonoBehaviour.h"

class Bullet : public MonoBehaviour
{
    shared_ptr<Shader> renderShader = make_shared<Shader>(L"23. RenderDemo.fx");

    virtual void Start() override;
    virtual void Update() override;

public:
    shared_ptr<Model> GetObject() { return _bullet; }
    void SetObject(shared_ptr<Model> bullet) { _bullet = bullet; }

    Vec3 StartPos;
    void Init(Vec3 StartPos, Vec3 dir);
    void Delete();

private:
    vector<GameObject> bulletList;
    shared_ptr<Model> _bullet;
    shared_ptr<Transform> _transform;

    Vec3 direction;   // 총알 이동 방향
    float speed = 5.f;      // 총알 속도
};


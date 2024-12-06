#pragma once
#include "Component.h"

enum class UiType
{
    NONE,
    SLIDER,
    BUTTON,

    END,
};

class Ui :
    public Component
{
    using Super = Component;
public:
    Ui(UiType type) : Super(ComponentType::UI), _type(type) {};
    virtual ~Ui() = default;
public:
    void SetOwner(weak_ptr<GameObject> obj);
    const shared_ptr<GameObject> GetOwner() { return _owner.lock(); };
    void SetActive(bool active) { _isVisible = active; };
    const bool GetActive() { return _isVisible; };

    virtual void Create(Vec3 screenPos, Vec2 size, shared_ptr<class Material> material) { };
    virtual void Update() { };
protected:
    void PreUpdate();
protected:
    UiType _type = UiType::NONE;
    bool _isVisible = false;

    // 오너가 있으면 active=false로 시작.
    weak_ptr<GameObject> _owner;
};


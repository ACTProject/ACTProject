#include "pch.h"
#include "Ui.h"
#include "Camera.h"

void Ui::SetOwner(weak_ptr<GameObject> obj)
{
    _owner = obj;
}

void Ui::PreUpdate()
{
    ImGui::Checkbox("visible", &_isVisible);

    shared_ptr<GameObject> owner = _owner.lock();
    if (owner != nullptr)
    {
        // 오너 트랜스폼을 화면 좌표계로 변환해서 뿌려야함.
        //Vec3 pos = owner->GetTransform()->GetLocalPosition();
        //pos.y = {pos.y + 3.0f};
        Vec3 pos;

        Matrix worldMat = owner->GetTransform()->GetWorldMatrix();
        Matrix viewMat = worldMat * Camera::S_MatView;
        Matrix projMat = viewMat * Camera::S_MatProjection;





        GetGameObject()->GetTransform()->SetLocalPosition(pos);
        int a = 0;
    }
}

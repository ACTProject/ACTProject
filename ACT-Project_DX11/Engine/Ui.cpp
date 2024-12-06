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
        Vec3 pos = owner->GetTransform()->GetLocalPosition();
        pos += Vec3{ 0.0f, 3.0f, 0.0f };

        Vec3 uiVeiwpos = XMVector3Transform(pos, Camera::S_MatView);
        Vec3 uiClipPos = XMVector3Transform(uiVeiwpos,Camera::S_MatProjection);
        float d = sqrt(uiClipPos.x * uiClipPos.x + uiClipPos.y * uiClipPos.y + uiClipPos.z * uiClipPos.z);

        float xNDC = uiClipPos.x / d;
        float yNDC = uiClipPos.y / d;

        float screenX = (xNDC+ 1.0f) * 0.5f * 800;
        float screenY = (1.0f - yNDC) * 0.5f * 600;
        //float screenX = 
        //float screenY = 
        //Vec3 screen = {screenX,screenY,0.0f};

       // GetGameObject()->GetTransform()->SetLocalPosition(screen);
        int a = 0;
    }
}

#include "pch.h"
#include "Slider.h"
#include "pch.h"
#include "Slider.h"
#include "MeshRenderer.h"

Slider::Slider() : Super(UiType::SLIDER)
{

}

Slider::~Slider()
{
}

void Slider::Update()
{
    Super::PreUpdate();

    if (ImGui::Button("Decrease Slider"))
    {
        _uvRatio -= 0.1f; // 감소량 조절 (예: 0.1f만큼 감소)
        if (_uvRatio < 0.0f) // 최소값 제한
        {
            _uvRatio = 0.0f;
        }
    }

    ImGui::SliderFloat("SliderTest", &_uvRatio, 0.0f, 1.0f);

    if (_isVisible == true)
    {
        if (GetOwner() != nullptr)
        {
            if (GetOwner()->GetGameObjectType() == GameObjectType::ENEMY)
            {
                // 슬라이더같은 경우는 setOwner를 해놨을 테니까.
                // 그냥 owner hp랑 공유를 시킬까.

                // 움직임은 직교투영에 xy값만 계속 바꾸면 될 듯.
                //Vec3 pos = GetOwner()->GetTransform()->GetLocalPosition();
                //GetGameObject()->GetTransform()->SetLocalPosition(pos);
            }
        }
        UpdateScale();
    }
}

void Slider::Create(Vec3 screenPos, Vec2 size, shared_ptr<class Material> material)
{
	auto go = _gameObject.lock();


	go->GetOrAddTransform()->SetLocalPosition(Vec3(screenPos.x,screenPos.y, screenPos.z));
	go->GetOrAddTransform()->SetScale(Vec3(size.x, size.y, 1.0f));

	float height = GRAPHICS->GetViewport().GetHeight();
	float width = GRAPHICS->GetViewport().GetWidth();

	go->GetTransform()->SetLocalCenter(Vec3{ 0.5f,0.0f,0.0f });

	_maxRatio = size.x;

	go->SetLayerIndex(Layer_UI);

	if (go->GetMeshRenderer() == nullptr)
		go->AddComponent(make_shared<MeshRenderer>());

	go->GetMeshRenderer()->SetMaterial(material);


	auto mesh = RESOURCES->Get<Mesh>(L"Quad");
	go->GetMeshRenderer()->SetMesh(mesh);
	go->GetMeshRenderer()->SetPass(0);
	go->GetMeshRenderer()->SetAlphaBlend(true);
}

void Slider::UpdateScale()
{
    auto go = _gameObject.lock();
    Vec3 vecScale = go->GetTransform()->GetLocalScale();
    go->GetTransform()->SetLocalScale(Vec3(_maxRatio * _uvRatio, vecScale.y, vecScale.z));
}

#include "pch.h"
#include "Slider.h"
#include "pch.h"
#include "Slider.h"
#include "MeshRenderer.h"

Slider::Slider() : Super(ComponentType::Slider)
{

}

Slider::~Slider()
{
}

void Slider::Update()
{
	ImGui::SliderFloat("SliderTest", &_uvRatio, 0.0f, 1.0f);

	// 이 부분은 나중에 데미지 처리될 때 데미지가 들어오면 호출되는 함수로 넣을 예정.
	auto go = _gameObject.lock();
	Vec3 vecScale = go->GetTransform()->GetLocalScale();
	go->GetTransform()->SetLocalScale(Vec3(_maxRatio * _uvRatio, vecScale.y, vecScale.z));
}

void Slider::Create(Vec2 screenPos, Vec2 size, shared_ptr<class Material> material)
{
	auto go = _gameObject.lock();


	go->GetOrAddTransform()->SetLocalPosition(Vec3(screenPos.x,screenPos.y, 0.0f));
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

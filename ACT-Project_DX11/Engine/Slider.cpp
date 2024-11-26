#include "pch.h"
#include "Slider.h"

#include "pch.h"
#include "Slider.h"
#include "MeshRenderer.h"
#include "Material.h"

Slider::Slider() : Super(ComponentType::Slider)
{

}

Slider::~Slider()
{
}

void Slider::Update()
{

	ImGui::SliderFloat("SliderTest", &_uvRatio,0.0f, 100.0f);

}

bool Slider::Picked(POINT screenPos)
{
	return ::PtInRect(&_rect, screenPos);
}

void Slider::Create(Vec2 screenPos, Vec2 size, shared_ptr<class Material> material)
{
	auto go = _gameObject.lock();

	float height = GRAPHICS->GetViewport().GetHeight();
	float width = GRAPHICS->GetViewport().GetWidth();

	float x = screenPos.x - width / 2;
	float y = height / 2 - screenPos.y;
	Vec3 position = Vec3(x, y, 0);

	go->GetOrAddTransform()->SetPosition(position);
	go->GetOrAddTransform()->SetScale(Vec3(size.x, size.y, 1));

	go->SetLayerIndex(Layer_UI);

	if (go->GetMeshRenderer() == nullptr)
		go->AddComponent(make_shared<MeshRenderer>());

	go->GetMeshRenderer()->SetMaterial(material);


	auto mesh = RESOURCES->Get<Mesh>(L"Quad");
	go->GetMeshRenderer()->SetMesh(mesh);
	go->GetMeshRenderer()->SetPass(0);
	go->GetMeshRenderer()->SetAlphaBlend(true);


}

void Slider::AddOnClickedEvent(std::function<void(void)> func)
{
	_onClicked = func;
}

void Slider::InvokeOnClicked()
{
	if (_onClicked)
		_onClicked();
}

// 클라이언트의 init에서 게임옵젝으로 추가함
// 버튼데모참고.
//
//// Material
//{
//	shared_ptr<Material> material = make_shared<Material>();
//	material->SetShader(_shader);
//	auto texture = RESOURCES->Load<Texture>(L"Veigar", L"..\\Resources\\Textures\\veigar.jpg");
//	material->SetDiffuseMap(texture);
//	MaterialDesc& desc = material->GetMaterialDesc();
//	desc.ambient = Vec4(1.f);
//	desc.diffuse = Vec4(1.f);
//	desc.specular = Vec4(1.f);
//	RESOURCES->Add(L"Veigar", material);
//}
//
//// Mesh
//{
//	auto obj = make_shared<GameObject>();
//	obj->AddComponent(make_shared<Button>());
//
//	obj->GetButton()->Create(Vec2(100, 100), Vec2(100, 100), RESOURCES->Get<Material>(L"Veigar"));
//
//	obj->GetButton()->AddOnClickedEvent([obj]() { CUR_SCENE->Remove(obj); });
//
//	CUR_SCENE->Add(obj);
//}
//
//// Mesh
//{
//	auto obj = make_shared<GameObject>();
//	obj->GetOrAddTransform()->SetLocalPosition(Vec3(0.f));
//	obj->GetOrAddTransform()->SetScale(Vec3(2.f));
//	obj->AddComponent(make_shared<MeshRenderer>());
//	{
//		obj->GetMeshRenderer()->SetMaterial(RESOURCES->Get<Material>(L"Veigar"));
//	}
//	{
//		auto mesh = RESOURCES->Get<Mesh>(L"Sphere");
//		obj->GetMeshRenderer()->SetMesh(mesh);
//		obj->GetMeshRenderer()->SetPass(0);
//	}
//
//	CUR_SCENE->Add(obj);
//}
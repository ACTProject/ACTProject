#include "pch.h"
#include "RawBuffer.h"
#include "TextureBuffer.h"
#include "Material.h"
#include "SkyDemo.h"
#include "GeometryHelper.h"
#include "Camera.h"
#include "GameObject.h"
#include "CameraScript.h"
#include "MeshRenderer.h"
#include "Mesh.h"
#include "Material.h"
#include "Model.h"
#include "ModelRenderer.h"
#include "ModelAnimator.h"
#include "Mesh.h"
#include "Transform.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Light.h"
#include "Graphics.h"
#include "SphereCollider.h"
#include "Scene.h"
#include "AABBBoxCollider.h"
#include "OBBBoxCollider.h"
#include "Terrain.h"
#include "Camera.h"
#include "Button.h"

void SkyDemo::Init()
{
	_shader = make_shared<Shader>(L"18. SkyDemo.fx");

	RESOURCES->Init();
	shared_ptr<Material> material = make_shared<Material>();
	material->SetShader(_shader);
	auto texture = RESOURCES->Load<Texture>(L"SKY", L"../Resources/Textures/Terrain/Sky01.jpg");
	material->SetDiffuseMap(texture);
	MaterialDesc& desc = material->GetMaterialDesc();
	desc.ambient = Vec4(1.f);
	desc.diffuse = Vec4(1.f);
	desc.specular = Vec4(1.f);
	RESOURCES->Add(L"SKY", material);

	auto obj = make_shared<GameObject>();
	obj->GetOrAddTransform();
	obj->AddComponent(make_shared<MeshRenderer>());
	{
		auto mesh = RESOURCES->Get<Mesh>(L"Sphere");
		obj->GetMeshRenderer()->SetMesh(mesh);
	}
	{
		auto material = RESOURCES->Get<Material>(L"SKY");
		obj->GetMeshRenderer()->SetMaterial(material);
	}
	
	CUR_SCENE->Add(obj);

	// Camera
	{
		auto camera = make_shared<GameObject>();
		camera->GetOrAddTransform()->SetPosition(Vec3{ 0.f, 0.f, -5.f });
		camera->AddComponent(make_shared<Camera>());
		camera->AddComponent(make_shared<CameraScript>());
		//camera->GetCamera()->SetCullingMaskLayerOnOff(Layer_UI, true);
		CUR_SCENE->Add(camera);
	}
}

void SkyDemo::Update()
{
	
}

void SkyDemo::Render()
{

}


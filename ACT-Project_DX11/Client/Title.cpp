#include "pch.h"
#include "Title.h"
#include "Camera.h"
#include "Button.h"
#include "RawBuffer.h"
#include "TextureBuffer.h"
#include "Material.h"
#include "GeometryHelper.h"
#include "Camera.h"
#include "GameObject.h"
#include "MeshRenderer.h"
#include "Mesh.h"
#include "Material.h"
#include "Mesh.h"
#include "Transform.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Light.h"
#include "Graphics.h"
#include "Scene.h"
#include "Camera.h"
#include "Billboard.h"
#include "CameraScript.h"


void Title::Init()
{
    shared_ptr<Shader> shader = make_shared<Shader>(L"23. RenderDemoUI.fx");

    // UI_Camera
    {
        auto camera = make_shared<GameObject>();
        camera->GetOrAddTransform()->SetPosition(Vec3{ 0.f, 0.f, -5.f });
        camera->AddComponent(make_shared<Camera>());
        camera->GetCamera()->SetProjectionType(ProjectionType::Orthographic);
        camera->GetCamera()->SetNear(1.f);
        camera->GetCamera()->SetFar(100.f);

        camera->GetCamera()->SetCullingMaskAll();
        camera->GetCamera()->SetCullingMaskLayerOnOff(Layer_UI, false);
        CUR_SCENE->Add(camera);
    }

    // Material
    {
        shared_ptr<Material> material = make_shared<Material>();
        material->SetShader(shader);
        auto texture = RESOURCES->Load<Texture>(L"Background", L"..\\Resources\\Textures\\UI\\title_background_8x6.png");
        material->SetDiffuseMap(texture);
        MaterialDesc& desc = material->GetMaterialDesc();
        desc.ambient = Vec4(1.f);
        desc.diffuse = Vec4(1.f);
        desc.specular = Vec4(1.f);
        RESOURCES->Add(L"Background", material);
    }

    // Material
    {
        shared_ptr<Material> material = make_shared<Material>();
        material->SetShader(shader);
        auto texture = RESOURCES->Load<Texture>(L"Logo", L"..\\Resources\\Textures\\UI\\title_logo.png");
        material->SetDiffuseMap(texture);
        MaterialDesc& desc = material->GetMaterialDesc();
        desc.ambient = Vec4(1.f);
        desc.diffuse = Vec4(1.f);
        desc.specular = Vec4(1.f);
        RESOURCES->Add(L"Logo", material);
    }

    // Material
    {
        shared_ptr<Material> material = make_shared<Material>();
        material->SetShader(shader);
        auto texture = RESOURCES->Load<Texture>(L"StardBtn", L"..\\Resources\\Textures\\UI\\Start_1.png");
        material->SetDiffuseMap(texture);
        MaterialDesc& desc = material->GetMaterialDesc();
        desc.ambient = Vec4(1.f);
        desc.diffuse = Vec4(1.f);
        desc.specular = Vec4(1.f);
        RESOURCES->Add(L"StardBtn", material);
    }

    // Material
    {
        shared_ptr<Material> material = make_shared<Material>();
        material->SetShader(shader);
        auto texture = RESOURCES->Load<Texture>(L"EndBtn", L"..\\Resources\\Textures\\UI\\End_0.png");
        material->SetDiffuseMap(texture);
        MaterialDesc& desc = material->GetMaterialDesc();
        desc.ambient = Vec4(1.f);
        desc.diffuse = Vec4(1.f);
        desc.specular = Vec4(1.f);
        RESOURCES->Add(L"EndBtn", material);
    }
    // Mesh
    {
        auto obj = make_shared<GameObject>();
        obj->GetOrAddTransform()->SetLocalPosition(Vec3(0.f, 0.f, 0.2f));
        obj->GetOrAddTransform()->SetScale(Vec3(800.f,600.f,0.f));
        obj->AddComponent(make_shared<MeshRenderer>());

        obj->SetLayerIndex(Layer_UI);
        {
            obj->GetMeshRenderer()->SetMaterial(RESOURCES->Get<Material>(L"Background"));
        }
        {
            auto mesh = RESOURCES->Get<Mesh>(L"Quad");
            obj->GetMeshRenderer()->SetMesh(mesh);
            obj->GetMeshRenderer()->SetPass(0);
        }

        CUR_SCENE->Add(obj);
    }

    // Mesh
    {
        auto obj = make_shared<GameObject>();
        obj->GetOrAddTransform()->SetLocalPosition(Vec3(-180.f, 170.f, 0.1f));
        obj->GetOrAddTransform()->SetScale(Vec3(400.f, 225.f, 0.f));
        obj->AddComponent(make_shared<MeshRenderer>());

        obj->SetLayerIndex(Layer_UI);
        {
            obj->GetMeshRenderer()->SetMaterial(RESOURCES->Get<Material>(L"Logo"));
        }
        {
            auto mesh = RESOURCES->Get<Mesh>(L"Quad");
            obj->GetMeshRenderer()->SetMesh(mesh);
            obj->GetMeshRenderer()->SetPass(0);
            obj->GetMeshRenderer()->SetAlphaBlend(true);
        }

        CUR_SCENE->Add(obj);
    }
    

    // Mesh
    {
        auto obj = make_shared<GameObject>();
        obj->AddComponent(make_shared<Button>());

        obj->GetButton()->Create(Vec3(100, 100, 0), Vec2(100, 100), RESOURCES->Get<Material>(L"Logo"));

        obj->GetButton()->AddOnClickedEvent([obj]() { CUR_SCENE->Remove(obj); });

        CUR_SCENE->Add(obj);
    }
}

void Title::Update()
{
}

void Title::Render()
{
}

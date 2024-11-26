#include "pch.h"
#include "RawBuffer.h"
#include "TextureBuffer.h"
#include "Material.h"
#include "Client.h"
#include "GeometryHelper.h"
#include "Camera.h"
#include "GameObject.h"
#include "CameraScript.h"
#include "PlayerScript.h"
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
#include "Billboard.h"
#include "RangoonScript.h"
#include "Rigidbody.h"
#include "Slider.h"

void Client::Init()
{
	shared_ptr<Shader> renderShader = make_shared<Shader>(L"23. RenderDemo.fx");

	// Camera
	{
		auto camera = make_shared<GameObject>();
		camera->GetOrAddTransform()->SetPosition(Vec3(0.f));
		camera->GetOrAddTransform()->SetLocalRotation(Vec3{ XMConvertToRadians(15), 0.f, 0.f });
		camera->AddComponent(make_shared<Camera>());
		{
			camera->GetCamera()->SetCameraOffset(Vec3(0.f, 7.f, -14.f));
		}
		//camera->AddComponent(make_shared<CameraScript>());
		camera->GetCamera()->SetCullingMaskLayerOnOff(Layer_UI, true);

		CUR_SCENE->Add(camera);
	}

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

	//UI_HPBar
	{
		// Material
		{
			shared_ptr<Material> material = make_shared<Material>();
			material->SetShader(renderShader);
			auto texture = RESOURCES->Load<Texture>(L"HealBar", L"..\\Resources\\Textures\\UI\\BackBorder_Health.png");
			material->SetDiffuseMap(texture);
			MaterialDesc& desc = material->GetMaterialDesc();
			desc.ambient = Vec4(1.f);
			desc.diffuse = Vec4(1.f);
			desc.specular = Vec4(1.f);
			RESOURCES->Add(L"HealBar", material);
		}
		// Material
		{
			shared_ptr<Material> material = make_shared<Material>();
			material->SetShader(renderShader);
			auto texture = RESOURCES->Load<Texture>(L"ArmorBar", L"..\\Resources\\Textures\\UI\\BackBorder_Armor.png");
			material->SetDiffuseMap(texture);
			MaterialDesc& desc = material->GetMaterialDesc();
			desc.ambient = Vec4(1.f);
			desc.diffuse = Vec4(1.f);
			desc.specular = Vec4(1.f);
			RESOURCES->Add(L"ArmorBar", material);
		}
		// Material
		{
			shared_ptr<Material> material = make_shared<Material>();
			material->SetShader(renderShader);
			auto texture = RESOURCES->Load<Texture>(L"RedBar", L"..\\Resources\\Textures\\UI\\Front_HPBar2.png");
			material->SetDiffuseMap(texture);
			MaterialDesc& desc = material->GetMaterialDesc();
			desc.ambient = Vec4(1.f);
			desc.diffuse = Vec4(1.f);
			desc.specular = Vec4(1.f);
			RESOURCES->Add(L"RedBar", material);
		}


		// MeshHealBar
		{
			auto obj = make_shared<GameObject>();
			obj->GetOrAddTransform()->SetLocalPosition(Vec3(-230.f, -260.f, 0.0f));
			obj->GetOrAddTransform()->SetScale(Vec3(180, 30, 100));
			obj->AddComponent(make_shared<MeshRenderer>());

			obj->SetLayerIndex(Layer_UI);
			{
				obj->GetMeshRenderer()->SetMaterial(RESOURCES->Get<Material>(L"HealBar"));

			}
			{
				auto mesh = RESOURCES->Get<Mesh>(L"Quad");
				obj->GetMeshRenderer()->SetMesh(mesh);
				obj->GetMeshRenderer()->SetPass(0);
				obj->GetMeshRenderer()->SetAlphaBlend(true);
			}

			CUR_SCENE->Add(obj);
		}
		// MeshArmorBar
		{
			auto obj = make_shared<GameObject>();
			obj->GetOrAddTransform()->SetLocalPosition(Vec3(-210.f, -230.f, -0.1f));
			obj->GetOrAddTransform()->SetScale(Vec3(200, 30, 100));
			obj->AddComponent(make_shared<MeshRenderer>());

			obj->SetLayerIndex(Layer_UI);
			{
				obj->GetMeshRenderer()->SetMaterial(RESOURCES->Get<Material>(L"ArmorBar"));

			}
			{
				auto mesh = RESOURCES->Get<Mesh>(L"Quad");
				obj->GetMeshRenderer()->SetMesh(mesh);
				obj->GetMeshRenderer()->SetAlphaBlend(true);
				obj->GetMeshRenderer()->SetPass(0);
			}

			CUR_SCENE->Add(obj);
		}
		// RedBar HPMesh
		{
			auto obj = make_shared<GameObject>();
			obj->GetOrAddTransform()->SetLocalPosition(Vec3(-228.f, -261.f, -0.2f));
			//obj->GetOrAddTransform()->SetScale(Vec3(150, 10, 100));
			obj->GetOrAddTransform()->SetScale(Vec3(126, 8, 100));

			obj->AddComponent(make_shared<MeshRenderer>());

			obj->SetLayerIndex(Layer_UI);
			{
				obj->GetMeshRenderer()->SetMaterial(RESOURCES->Get<Material>(L"RedBar"));

			}
			{
				auto mesh = RESOURCES->Get<Mesh>(L"Quad");
				obj->GetMeshRenderer()->SetMesh(mesh);
				obj->GetMeshRenderer()->SetAlphaBlend(true);
				obj->GetMeshRenderer()->SetPass(0);
			}

			CUR_SCENE->Add(obj);
		}

		// RedBar ARmor Mesh
		{
			auto obj = make_shared<GameObject>();
			obj->GetOrAddTransform()->SetLocalPosition(Vec3(-207.f, -234.f, -0.2f));
			obj->GetOrAddTransform()->SetScale(Vec3(164, 7, 100));

			obj->AddComponent(make_shared<MeshRenderer>());

			obj->SetLayerIndex(Layer_UI);
			{
				obj->GetMeshRenderer()->SetMaterial(RESOURCES->Get<Material>(L"RedBar"));

			}
			{
				auto mesh = RESOURCES->Get<Mesh>(L"Quad");
				obj->GetMeshRenderer()->SetMesh(mesh);
				//obj->GetMeshRenderer()->SetAlphaBlend(true);
				obj->GetMeshRenderer()->SetPass(0);
			}

			CUR_SCENE->Add(obj);
		}

		// Mesh
		{
			auto obj = make_shared<GameObject>();
			obj->AddComponent(make_shared<Slider>());

			obj->GetSlider()->Create(Vec2(100, 100), Vec2(100, 100), RESOURCES->Get<Material>(L"HealBar"));

			//obj->GetButton()->AddOnClickedEvent([obj]() { CUR_SCENE->Remove(obj); });

			CUR_SCENE->Add(obj);
		}

	}

	// Light
	{
		auto light = make_shared<GameObject>();
		light->AddComponent(make_shared<Light>());
		LightDesc lightDesc;
		lightDesc.ambient = Vec4(0.4f);
		lightDesc.diffuse = Vec4(1.f);
		lightDesc.specular = Vec4(0.1f);
		lightDesc.direction = Vec3(1.f, 0.f, 1.f);
		light->GetLight()->SetLightDesc(lightDesc);
		CUR_SCENE->Add(light);
	}

	// Player
	auto player = make_shared<GameObject>();

	
		// Player
		player->GetOrAddTransform()->SetPosition(Vec3(1, 0, 1));
		player->GetOrAddTransform()->SetLocalRotation(Vec3(0, 0, 0)); // XMConvertToRadians()
		player->GetOrAddTransform()->SetScale(Vec3(0.01f));

		shared_ptr<Model> playerModel = make_shared<Model>();
		// Player::Model
		{
			playerModel->ReadModel(L"Player/Player");
			playerModel->ReadMaterial(L"Player/Player");

			playerModel->ReadAnimation(L"Player/Idle", AnimationState::Idle);
			playerModel->ReadAnimation(L"Player/Walk", AnimationState::Walk);
			playerModel->ReadAnimation(L"Player/Run", AnimationState::Run);
			playerModel->ReadAnimation(L"Player/Crab_Atk_Combo1", AnimationState::Attack1);
			playerModel->ReadAnimation(L"Player/Crab_Atk_Combo2", AnimationState::Attack2);
			playerModel->ReadAnimation(L"Player/Crab_Atk_Combo3", AnimationState::Attack3);
			playerModel->ReadAnimation(L"Player/Crab_Atk_Combo4", AnimationState::Attack4);

			//playerModel->ReadAnimation(L"Player/Crab_Death");
			//playerModel->ReadAnimation(L"Player/Crab_GetUp");

			// Weapon
			shared_ptr<Model> weaponModel = make_shared<Model>();
			{
				// CustomData -> Memory
				weaponModel->ReadModel(L"Fork/Fork");
				weaponModel->ReadMaterial(L"Fork/Fork");
			}

			ModelMesh& weaponMesh = *weaponModel->GetMeshes()[0];
			playerModel->AddDummyBoneAndAttach(weaponMesh, L"Hand_Grip_L", L"WeaponDummy");
		}

		// Player::ModelAnimator
		shared_ptr<ModelAnimator> ma1 = make_shared<ModelAnimator>(renderShader);
		player->AddComponent(ma1);
		{
			player->GetModelAnimator()->SetModel(playerModel);
			player->GetModelAnimator()->SetPass(2);
		}
		// Rigidbody
		shared_ptr<Rigidbody> rigidBody = make_shared<Rigidbody>();
		rigidBody->SetUseGravity(true);
		player->AddComponent(rigidBody);

		// Player::PlayerScript
		shared_ptr<PlayerScript> playerScript = make_shared<PlayerScript>();

		playerScript->SetPlayer(playerModel);
		playerScript->SetModelAnimator(ma1);

		player->AddComponent(playerScript);

		CUR_SCENE->Add(player);
		CUR_SCENE->SetPlayer(player);
	

	// Enemy
	auto enemy = make_shared<GameObject>();
	{
		enemy->GetOrAddTransform()->SetPosition(Vec3(10, 0, 10));
		enemy->GetOrAddTransform()->SetLocalRotation(Vec3(0, 0, 0)); // XMConvertToRadians()
		enemy->GetOrAddTransform()->SetScale(Vec3(0.0001f));

		shared_ptr<Model> enemyModel = make_shared<Model>();
		// Model
		{
			enemyModel->ReadModel(L"Enemy/Rangoon");
			enemyModel->ReadMaterial(L"Enemy/Rangoon");

			enemyModel->ReadAnimation(L"Enemy/Rangoon_Taunt", AnimationState::Run);
			enemyModel->ReadAnimation(L"Enemy/Rangoon_idle", AnimationState::Idle);
			enemyModel->ReadAnimation(L"Enemy/Rangoon_hit", AnimationState::Hit);
			enemyModel->ReadAnimation(L"Enemy/Rangoon_atk", AnimationState::Atk);
		}
		shared_ptr<ModelAnimator> ma2 = make_shared<ModelAnimator>(renderShader);
		enemy->AddComponent(ma2);
		{
			enemy->GetModelAnimator()->SetModel(enemyModel);
			enemy->GetModelAnimator()->SetPass(2);
		}
		shared_ptr<RangoonScript> rangoon = make_shared<RangoonScript>();

		rangoon->SetEnemy(enemyModel);
		rangoon->SetModelAnimator(ma2);

		enemy->AddComponent(rangoon);	

		// Rigidbody
		shared_ptr<Rigidbody> rigidBody = make_shared<Rigidbody>();
		rigidBody->SetUseGravity(true);
		enemy->AddComponent(rigidBody);

		CUR_SCENE->Add(enemy);
	}

	//auto enemy2 = make_shared<GameObject>();
	//{
	//	enemy2->GetOrAddTransform()->SetPosition(Vec3(5, 0, 10));
	//	enemy2->GetOrAddTransform()->SetLocalRotation(Vec3(0, 0, 0)); // XMConvertToRadians()
	//	enemy2->GetOrAddTransform()->SetScale(Vec3(0.0001f));

	//	shared_ptr<Model> enemyModel = make_shared<Model>();
	//	// Model
	//	{
	//		enemyModel->ReadModel(L"Enemy/pistol");
	//		enemyModel->ReadMaterial(L"Enemy/pistol");

	//		enemyModel->ReadAnimation(L"Enemy/pistol_Idle", AnimationState::Idle);
	//		//enemyModel->ReadAnimation(L"Enemy/pistol_shoot", AnimationState::Hit);
	//		//enemyModel->ReadAnimation(L"Enemy/pistol_Idle", AnimationState::Atk);*/

	//	}
	//	shared_ptr<ModelAnimator> ma2 = make_shared<ModelAnimator>(renderShader);
	//	enemy2->AddComponent(ma2);
	//	{
	//		enemy2->GetModelAnimator()->SetModel(enemyModel);
	//		enemy2->GetModelAnimator()->SetPass(2);
	//	}
	//	CUR_SCENE->Add(enemy2);
	//}

	// Terrain
	{
		// Material

		shared_ptr<Material> material = make_shared<Material>();
		material->SetShader(renderShader);
		auto heightMap = RESOURCES->Load<Texture>(L"Height", L"../Resources/Textures/Terrain/height.png");
		//auto texture = RESOURCES->Load<Texture>(L"Sand", L"..\\Resources\\Textures\\Terrain\\SandMap.png");
		auto texture = RESOURCES->Load<Texture>(L"Sand", L"..\\Resources\\Textures\\Terrain\\testTile.png");

		const int32 width = heightMap->GetSize().x;
		const int32 height = heightMap->GetSize().y;

		const DirectX::ScratchImage& info = heightMap->GetInfo();

		// Replace the old heightmap with the filtered one.
		uint8* pixelBuffer = info.GetPixels();

		material->SetDiffuseMap(texture);
		MaterialDesc& desc = material->GetMaterialDesc();
		desc.ambient = Vec4(1.f);
		desc.diffuse = Vec4(1.f);
		desc.specular = Vec4(1.f);
		RESOURCES->Add(L"Sand", material);


		auto obj = make_shared<GameObject>();
		obj->AddComponent(make_shared<Terrain>());
		obj->GetTerrain()->Create(width, height, RESOURCES->Get<Material>(L"Sand"));
		{
			vector<VertexTextureNormalTangentData>& v = const_cast<vector<VertexTextureNormalTangentData>&>(obj->GetTerrain()->GetMesh()->GetGeometry()->GetVertices());
			for (int32 z = 0; z < height; z++)
			{
				for (int32 x = 0; x < width; x++)
				{
					int32 idx = width * z + x;
					uint8 height = pixelBuffer[idx] / 255.f * 25.f;
					v[idx].position.y = height - 8.f;
				}
			}

			// Smooth
			float avg = 0.0f;
			float num = 0.0f;

			for (int32 z = 0; z < height; z++)
			{
				for (int32 x = 0; x < width; x++)
				{
					avg = 0.0f;
					num = 0.0f;
					for (int32 m = z - 1; m <= z + 1; ++m) // -1 ~ 1, 0 ~ 2
					{

						for (int32 n = x - 1; n <= x + 1; ++n)
						{
							if (m >= 0 && m < (int32)height &&
								n >= 0 && n < (int32)width)
							{
								avg += v[m * width + n].position.y;
								num += 1.0f;
							}
						}

					}
					v[z * height + x].position.y = avg / num;

				}
			}

		}

		obj->GetTerrain()->GetMesh()->GetVertexBuffer()->Create(obj->GetTerrain()->GetMesh()->GetGeometry()->GetVertices());
		obj->GetTerrain()->GetMesh()->GetIndexBuffer()->Create(obj->GetTerrain()->GetMesh()->GetGeometry()->GetIndices());

		CUR_SCENE->SetTerrain(obj);
		CUR_SCENE->Add(obj);
	}
}

void Client::Update()
{
	
}

void Client::Render()
{

}

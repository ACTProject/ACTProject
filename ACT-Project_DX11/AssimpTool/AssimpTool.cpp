#include "pch.h"
#include "AssimpTool.h"
#include "Converter.h"

void AssimpTool::Init()
{
	{
		{
			shared_ptr<Converter> converter = make_shared<Converter>();

			// FBX -> Memory
			converter->ReadAssetFile(L"Fork/Fork.fbx");

			// Memory -> CustomData (File)
			converter->ExportMaterialData(L"Fork/Fork");
			converter->ExportModelData(L"Fork/Fork");

			// CustomData (File) -> Memory
		}

		{
			shared_ptr<Converter> converter = make_shared<Converter>();
			converter->ReadAssetFile(L"Player/Player.fbx");
			converter->ExportMaterialData(L"Player/Player");
			converter->ExportModelData(L"Player/Player");
		}
		{
			shared_ptr<Converter> converter = make_shared<Converter>();
			converter->ReadAssetFile(L"Player/Crab_Idle.fbx");
			converter->ExportAnimationData(L"Player/Idle");
		}
		{
			shared_ptr<Converter> converter = make_shared<Converter>();
			converter->ReadAssetFile(L"Player/Crab_Walk.fbx");
			converter->ExportAnimationData(L"Player/Walk");
		}
		{
			shared_ptr<Converter> converter = make_shared<Converter>();
			converter->ReadAssetFile(L"Player/Crab_Run.fbx");
			converter->ExportAnimationData(L"Player/Run");
		}
		{
			shared_ptr<Converter> converter = make_shared<Converter>();
			converter->ReadAssetFile(L"Player/Crab_Atk_Combo1.fbx");
			converter->ExportAnimationData(L"Player/Crab_Atk_Combo1");
		}
		{
			shared_ptr<Converter> converter = make_shared<Converter>();
			converter->ReadAssetFile(L"Player/Crab_Atk_Combo2.fbx");
			converter->ExportAnimationData(L"Player/Crab_Atk_Combo2");
		}
		{
			shared_ptr<Converter> converter = make_shared<Converter>();
			converter->ReadAssetFile(L"Player/Crab_Atk_Combo3.fbx");
			converter->ExportAnimationData(L"Player/Crab_Atk_Combo3");
		}
		{
			shared_ptr<Converter> converter = make_shared<Converter>();
			converter->ReadAssetFile(L"Player/Crab_Atk_Combo4.fbx");
			converter->ExportAnimationData(L"Player/Crab_Atk_Combo4");
		}
		{
			shared_ptr<Converter> converter = make_shared<Converter>();
			converter->ReadAssetFile(L"Enemy/Rangoon_mesh.fbx");
			converter->ExportMaterialData(L"Enemy/Rangoon");
			converter->ExportModelData(L"Enemy/Rangoon");
		}
		{
			shared_ptr<Converter> converter = make_shared<Converter>();
			converter->ReadAssetFile(L"Enemy/Rangoon_idle.fbx");
			converter->ExportAnimationData(L"Enemy/Rangoon_idle");
		}
		{
			shared_ptr<Converter> converter = make_shared<Converter>();
			converter->ReadAssetFile(L"Enemy/Rangoon_hit.fbx");
			converter->ExportAnimationData(L"Enemy/Rangoon_hit");
		}
		{
			shared_ptr<Converter> converter = make_shared<Converter>();
			converter->ReadAssetFile(L"Enemy/Rangoon_atk.fbx");
			converter->ExportAnimationData(L"Enemy/Rangoon_atk");
		}
		{
			shared_ptr<Converter> converter = make_shared<Converter>();
			converter->ReadAssetFile(L"Enemy/pistol_mesh.fbx");
			converter->ExportMaterialData(L"Enemy/pistol");
			converter->ExportModelData(L"Enemy/pistol");
		}
		{
			shared_ptr<Converter> converter = make_shared<Converter>();
			converter->ReadAssetFile(L"Enemy/pistol_Idle.fbx");
			converter->ExportAnimationData(L"Enemy/pistol_Idle");
		}
		{
			shared_ptr<Converter> converter = make_shared<Converter>();
			converter->ReadAssetFile(L"Enemy/pistol_shoot.fbx");
			converter->ExportAnimationData(L"Enemy/pistol_shoot");
		}
		{
			shared_ptr<Converter> converter = make_shared<Converter>();
			converter->ReadAssetFile(L"Obj/TutorialWallsLeft.fbx");
			converter->ExportMaterialData(L"Obj/TutorialWallsLeft");
			converter->ExportModelData(L"Obj/TutorialWallsLeft");
		}


		//test
		// 
		//{
		//	shared_ptr<Converter> converter = make_shared<Converter>();
		//	converter->ReadAssetFile(L"Player/Crab_Death.fbx");
		//	converter->ExportAnimationData(L"Player/Crab_Death");
		//}
		//{
		//	shared_ptr<Converter> converter = make_shared<Converter>();
		//	converter->ReadAssetFile(L"Player/Crab_GetUp.fbx");
		//	converter->ExportAnimationData(L"Player/Crab_GetUp");
		//}
	}
}

void AssimpTool::Update()
{

}

void AssimpTool::Render()
{

}

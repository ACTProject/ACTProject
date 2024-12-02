#include "pch.h"
#include "AssimpTool.h"
#include "Converter.h"

void AssimpTool::Init()
{
	// Weapon
	{
		shared_ptr<Converter> converter = make_shared<Converter>();

		// FBX -> Memory
		converter->ReadAssetFile(L"Fork/Fork.fbx");

		// Memory -> CustomData (File)
		converter->ExportMaterialData(L"Fork/Fork");
		converter->ExportModelData(L"Fork/Fork");

		// CustomData (File) -> Memory
	}

	// Player
	{
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
	}
	// Enemy
	{
		{
			shared_ptr<Converter> converter = make_shared<Converter>();
			converter->ReadAssetFile(L"Enemy/Rangoon_mesh.fbx");
			converter->ExportMaterialData(L"Enemy/Rangoon");
			converter->ExportModelData(L"Enemy/Rangoon");
		}
		{
			shared_ptr<Converter> converter = make_shared<Converter>();
			converter->ReadAssetFile(L"Enemy/Rangoon_aggro.fbx");
			converter->ExportAnimationData(L"Enemy/Rangoon_aggro");
		}
		{
			shared_ptr<Converter> converter = make_shared<Converter>();
			converter->ReadAssetFile(L"Enemy/Rangoon_atkBigSnippy.fbx");
			converter->ExportAnimationData(L"Enemy/Rangoon_atkBigSnippy");
		}
		{
			shared_ptr<Converter> converter = make_shared<Converter>();
			converter->ReadAssetFile(L"Enemy/Rangoon_atkSmallSnippy.fbx");
			converter->ExportAnimationData(L"Enemy/Rangoon_atkSmallSnippy");
		}
		{
			shared_ptr<Converter> converter = make_shared<Converter>();
			converter->ReadAssetFile(L"Enemy/Rangoon_atkSmash.fbx");
			converter->ExportAnimationData(L"Enemy/Rangoon_atkSmash");
		}
		{
			shared_ptr<Converter> converter = make_shared<Converter>();
			converter->ReadAssetFile(L"Enemy/Rangoon_die.fbx");
			converter->ExportAnimationData(L"Enemy/Rangoon_die");
		}
		{
			shared_ptr<Converter> converter = make_shared<Converter>();
			converter->ReadAssetFile(L"Enemy/Rangoon_hit.fbx");
			converter->ExportAnimationData(L"Enemy/Rangoon_hit");
		}
		{
			shared_ptr<Converter> converter = make_shared<Converter>();
			converter->ReadAssetFile(L"Enemy/Rangoon_idle.fbx");
			converter->ExportAnimationData(L"Enemy/Rangoon_idle");
		}
		{
			shared_ptr<Converter> converter = make_shared<Converter>();
			converter->ReadAssetFile(L"Enemy/Rangoon_roar.fbx");
			converter->ExportAnimationData(L"Enemy/Rangoon_roar");
		}
		{
			shared_ptr<Converter> converter = make_shared<Converter>();
			converter->ReadAssetFile(L"Enemy/Rangoon_run.fbx");
			converter->ExportAnimationData(L"Enemy/Rangoon_run");
		}
	}
	// MapObject
	{
		{
			shared_ptr<Converter> converter = make_shared<Converter>();
			converter->ReadAssetFile(L"MapObject/recyclingBox01.fbx");
			converter->ExportMaterialData(L"MapObject/recyclingBox01");
			converter->ExportModelData(L"MapObject/recyclingBox01");
		}
		{
			shared_ptr<Converter> converter = make_shared<Converter>();
			converter->ReadAssetFile(L"MapObject/WallLeft.fbx");
			converter->ExportMaterialData(L"MapObject/WallLeft");
			converter->ExportModelData(L"MapObject/WallLeft");
		}
		{
			shared_ptr<Converter> converter = make_shared<Converter>();
			converter->ReadAssetFile(L"MapObject/flagpole.fbx");
			converter->ExportMaterialData(L"MapObject/flagpole");
			converter->ExportModelData(L"MapObject/flagpole");
		}
		{
			shared_ptr<Converter> converter = make_shared<Converter>();
			converter->ReadAssetFile(L"MapObject/pigeon.fbx");
			converter->ExportMaterialData(L"MapObject/pigeon");
			converter->ExportModelData(L"MapObject/pigeon");
		}
		{
			shared_ptr<Converter> converter = make_shared<Converter>();
			converter->ReadAssetFile(L"MapObject/StarFish.fbx");
			converter->ExportMaterialData(L"MapObject/StarFish");
			converter->ExportModelData(L"MapObject/StarFish");
		}
		{
			shared_ptr<Converter> converter = make_shared<Converter>();
			converter->ReadAssetFile(L"MapObject/PencilHedgehog.fbx");
			converter->ExportMaterialData(L"MapObject/PencilHedgehog");
			converter->ExportModelData(L"MapObject/PencilHedgehog");
		}
	}
}

void AssimpTool::Update()
{

}

void AssimpTool::Render()
{

}

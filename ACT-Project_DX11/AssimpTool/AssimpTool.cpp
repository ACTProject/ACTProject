#include "pch.h"
#include "AssimpTool.h"
#include "Converter.h"

void AssimpTool::Init()
{
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

		// MapObject
		{
			shared_ptr<Converter> converter = make_shared<Converter>();
			converter->ReadAssetFile(L"Obj/recyclingBox01.fbx");
			converter->ExportMaterialData(L"Obj/recyclingBox01");
			converter->ExportModelData(L"Obj/recyclingBox01");
		}
		{
			shared_ptr<Converter> converter = make_shared<Converter>();
			converter->ReadAssetFile(L"Obj/WallLeft.fbx");
			converter->ExportMaterialData(L"Obj/WallLeft");
			converter->ExportModelData(L"Obj/WallLeft");
		}
		{
			shared_ptr<Converter> converter = make_shared<Converter>();
			converter->ReadAssetFile(L"Obj/flagpole.fbx");
			converter->ExportMaterialData(L"Obj/flagpole");
			converter->ExportModelData(L"Obj/flagpole");
		}
		{
			shared_ptr<Converter> converter = make_shared<Converter>();
			converter->ReadAssetFile(L"Obj/pigeon.fbx");
			converter->ExportMaterialData(L"Obj/pigeon");
			converter->ExportModelData(L"Obj/pigeon");
		}
		{
			shared_ptr<Converter> converter = make_shared<Converter>();
			converter->ReadAssetFile(L"Obj/StarFish.fbx");
			converter->ExportMaterialData(L"Obj/StarFish");
			converter->ExportModelData(L"Obj/StarFish");
		}
		{
			shared_ptr<Converter> converter = make_shared<Converter>();
			converter->ReadAssetFile(L"Obj/PencilHedgehog.fbx");
			converter->ExportMaterialData(L"Obj/PencilHedgehog");
			converter->ExportModelData(L"Obj/PencilHedgehog");
		}
	}
}

void AssimpTool::Update()
{

}

void AssimpTool::Render()
{

}

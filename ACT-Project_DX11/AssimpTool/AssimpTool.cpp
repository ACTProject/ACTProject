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

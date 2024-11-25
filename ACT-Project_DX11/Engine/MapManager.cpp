#include "pch.h"
#include "MapManager.h"
#include "MeshRenderer.h"
#include "ModelRenderer.h"
#include "Model.h"
#include "InputManager.h"

#include "AABBBoxCollider.h"
#include "SceneManager.h"


void MapManager::Init()
{
	ImportMapObj();
	
}

void MapManager::Update()
{
	// select 오브젝트 바꾸면서 
	if (InputManager::GetInstance()->GetButton(KEY_TYPE::KEY_3))
	{
		_selectObject = _mapInfoList[MapObjSelect::START];
	}
	else if (InputManager::GetInstance()->GetButton(KEY_TYPE::KEY_4))
	{
		_selectObject = _mapInfoList[MapObjSelect::START + 1];
	}
	else
	{
		_selectObject = nullptr;
	}

}

shared_ptr<GameObject> MapManager::Create(Vec3& pos)
{
	shared_ptr<GameObject> obj = make_shared<GameObject>();
	{
		obj->GetOrAddTransform()->SetPosition(pos);
		obj->GetOrAddTransform()->SetLocalRotation(Vec3(0, 0, 0)); // XMConvertToRadians()
		obj->GetOrAddTransform()->SetScale(_selectObject->scale);

		shared_ptr<Model> model = make_shared<Model>();
		{
			model->ReadModel(_selectObject->filename);
			model->ReadMaterial(_selectObject->filename);
		}
		shared_ptr<Shader> renderShader = make_shared<Shader>(_selectObject->shadername);
		auto modelrender = make_shared<ModelRenderer>(renderShader);
		obj->AddComponent(modelrender);
		obj->GetModelRenderer()->SetModel(model);
		obj->GetModelRenderer()->SetPass(0);

		//Collider 박스 추가.
		//shared_ptr<AABBBoxCollider> collider = make_shared<AABBBoxCollider>(ColliderType::AABB);
		//collider;
		//obj->AddComponent(collider);
	}
	_mapObjList.push_back(obj);
	return obj;
}


shared_ptr<GameObject> MapManager::Create(MapObjDesc& desc)
{
	shared_ptr<GameObject> obj = make_shared<GameObject>();
	{
		obj->GetOrAddTransform()->SetPosition(desc.pos);
		obj->GetOrAddTransform()->SetLocalRotation(Vec3(0, 0, 0)); // XMConvertToRadians()
		obj->GetOrAddTransform()->SetScale(desc.scale);

		shared_ptr<Model> model = make_shared<Model>();
		{
			model->ReadModel(desc.filename);
			model->ReadMaterial(desc.filename);
		}
		shared_ptr<Shader> shader = make_shared<Shader>(desc.shadername);
		auto modelrender = make_shared<ModelRenderer>(shader);
		obj->AddComponent(modelrender);
		obj->GetModelRenderer()->SetModel(model);
		obj->GetModelRenderer()->SetPass(0);
	}
	_mapObjList.push_back(obj);
	return obj;
}


void MapManager::AddMapObj(shared_ptr<MapObjDesc> obj)
{
	_mapInfoList.push_back(obj);
}

bool MapManager::ExportMapObj()
{
	int length = _mapObjList.size();
		
	if (length <= 0)
	{
		return true;
	}

	FILE* fp = nullptr;
	errno_t err = _wfopen_s(&fp, _fileName.c_str(), L"wb");
	if (err != 0) return false;


	fwrite(&length, sizeof(int), 1, fp);
	MapObjDesc dec;
	for (int i = 0; i < length; i++)
	{
		dec.pos =			_mapObjList[i]->GetTransform()->GetLocalPosition(); 
		fwrite(&dec.pos, sizeof(Vec3), 1, fp);
		dec.scale =			_mapObjList[i]->GetTransform()->GetLocalScale();
		fwrite(&dec.scale, sizeof(Vec3), 1, fp);

		dec.filename = _mapObjList[i]->GetModelRenderer()->GetModel()->GetTextureName();
		dec.fileLength = dec.filename.length();
		wchar_t szLoadfilename[256] = { 0, };
		dec.filename.copy(szLoadfilename, dec.fileLength);
		fwrite(&dec.fileLength, sizeof(int), 1, fp);
		fwrite(&szLoadfilename, sizeof(wchar_t), dec.fileLength, fp);

		dec.shadername = _mapObjList[i]->GetModelRenderer()->GetShader()->GetFile();
		dec.shaderLength = dec.shadername.length();
		wchar_t szLoadShadername[256] = { 0, };
		dec.shadername.copy(szLoadShadername, dec.shaderLength);
		fwrite(&dec.shaderLength, sizeof(int), 1, fp);
		fwrite(&szLoadShadername, sizeof(wchar_t), dec.shaderLength, fp);
	}
	err = fclose(fp);
	if (err != 0) return false;
	_fcloseall();
	return true;
}

bool MapManager::ImportMapObj()
{
	FILE* fp = nullptr;
	errno_t err = _wfopen_s(&fp, _fileName.c_str(), L"rb");
	if (err != 0) return false;

	int lengths = 0;
	fread(&lengths, sizeof(int), 1, fp);

	MapObjDesc dec;
	for (int i = 0; i < lengths; i++)
	{
		fread(&dec.pos, sizeof(Vec3), 1, fp);
		fread(&dec.scale, sizeof(Vec3), 1, fp);

		fread(&dec.fileLength, sizeof(int), 1, fp);
		wchar_t szLoadfilename[256] = { 0, };
		fread(szLoadfilename, sizeof(wchar_t), dec.fileLength, fp);
		dec.filename = szLoadfilename;

		fread(&dec.shaderLength, sizeof(int), 1, fp);
		wchar_t szLoadshadername[256] = { 0, };
		fread(szLoadshadername, sizeof(wchar_t), dec.shaderLength, fp);
		dec.shadername = szLoadshadername;

		Create(dec);
	}

	err = fclose(fp);
	if (err != 0) return false;
	_fcloseall();

	for (auto gameObj : _mapObjList)
	{
		SCENE->GetCurrentScene()->Add(gameObj);
	}
	return true;
}


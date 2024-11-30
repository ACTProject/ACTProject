#include "pch.h"
#include "MapManager.h"
#include "MeshRenderer.h"
#include "ModelRenderer.h"
#include "Model.h"
#include "AABBBoxCollider.h"
#include "Terrain.h"
#include "AABBBoxCollider.h"
#include "CollisionManager.h"

void MapManager::Init()
{
	ImportMapObj();
}

bool MapManager::ChekMapObjectSelect(shared_ptr<GameObject> obj)
{
	for (auto& go : _mapObjList)
	{
		if (go == obj)
		{
			_mapSelectObj = go;
			return true;
		}
	}
	return false;
}

void MapManager::Update()
{
	if (DEBUG->IsDebugEnabled())
	{

		// 오브젝트 삭제 함수.
		if (_mapSelectObj != nullptr && InputManager::GetInstance()->GetButtonDown(KEY_TYPE::DELETEKEY))
		{
			RemoveMapObj();
		}

		ImGuiSelectMapObject();
		
		ImGui::RadioButton("Position", &_transformSelect, 0); ImGui::SameLine();
		ImGui::RadioButton("Rotation", &_transformSelect, 1); ImGui::SameLine();
		ImGui::RadioButton("Scale", &_transformSelect, 2); ImGui::SameLine();
		ImGui::RadioButton("Collider", &_transformSelect, 3);

		if (_mapSelectDesc != nullptr)
		{
			UpdateMapDescTransform();
		}
		if (_mapSelectObj != nullptr)
		{
			UpdateMapObjTransform();
		}

		// 실시간 클릭 시 해당 위치에 오브젝트 배치 하는 코드.
		if (INPUT->GetButtonDown(KEY_TYPE::RBUTTON))
		{
			POINT screenPt = INPUT->GetMousePos();
			SCENE->GetCurrentScene()->Pick(screenPt.x, screenPt.y);
		}


		// 선택한 오브젝트 트랜스폼 변경 함수.
		if (_mapSelectObj != nullptr && InputManager::GetInstance()->GetButton(KEY_TYPE::RBUTTON) && _transformSelect == 0)
		{
			ChangeMapObjPosition();
		}
		else if (_mapSelectObj != nullptr && InputManager::GetInstance()->GetButton(KEY_TYPE::RBUTTON) && _transformSelect == 1)
		{
			ChangeMapObjRotation();
		}
		else if (_mapSelectObj != nullptr && InputManager::GetInstance()->GetButton(KEY_TYPE::RBUTTON) && _transformSelect == 2)
		{
			ChangeMapObjScale();
		}


	}
}

shared_ptr<GameObject> MapManager::Create(Vec3& pos)
{
	shared_ptr<GameObject> obj = make_shared<GameObject>();
	{
		obj->GetOrAddTransform()->SetPosition(pos);
		obj->GetOrAddTransform()->SetLocalRotation(_mapSelectDesc->rotation);
		obj->GetOrAddTransform()->SetScale(_mapSelectDesc->scale);

		shared_ptr<Model> model = make_shared<Model>();
		{
			model->ReadModel(_mapSelectDesc->filename);
			model->ReadMaterial(_mapSelectDesc->filename);
		}
		shared_ptr<Shader> renderShader = make_shared<Shader>(_mapSelectDesc->shadername);
		auto modelrender = make_shared<ModelRenderer>(renderShader);
		obj->AddComponent(modelrender);
		obj->GetModelRenderer()->SetModel(model);
		obj->GetModelRenderer()->SetPass(1);


		if (_mapSelectDesc->isCollision == true)
		{
			auto collider = make_shared<AABBBoxCollider>();
			collider->SetOffset(_mapSelectDesc->offset);
			collider->GetBoundingBox().Extents = _mapSelectDesc->extent;
			obj->AddComponent(collider);
			COLLISION->AddCollider(collider);
		}
	}
	_mapObjList.push_back(obj);
	return obj;
}


shared_ptr<GameObject> MapManager::Create(MapObjDesc& desc)
{
	shared_ptr<GameObject> obj = make_shared<GameObject>();
	{
		obj->GetOrAddTransform()->SetPosition(desc.pos);
		obj->GetOrAddTransform()->SetLocalRotation(desc.rotation); // XMConvertToRadians()
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
		obj->GetModelRenderer()->SetPass(1);

		if (desc.isCollision == true)
		{
			auto collider = make_shared<AABBBoxCollider>();
			collider->SetOffset(desc.offset);
			collider->GetBoundingBox().Extents = desc.extent;
			obj->AddComponent(collider);
			COLLISION->AddCollider(collider);
		}
	}
	_mapObjList.push_back(obj);
	return obj;
}


void MapManager::AddMapObj(shared_ptr<MapObjDesc> obj)
{
	_mapInitInfoList.push_back(obj);
}

void MapManager::InitMapText()
{
	_fileTextList.resize(_mapInitInfoList.size());
	for (int i = 0; i < _fileTextList.size(); i++)
	{
		_fileTextList[i].assign(_mapInitInfoList[i]->filename.begin(), _mapInitInfoList[i]->filename.end());
	}
}

void MapManager::ImGuiSelectMapObject()
{
	ImGui::Begin("SelectMapObject");

	if (ImGui::BeginListBox(" "))
	{
		for (int i = 0; i < _fileTextList.size(); i++)
		{
			const bool is_selected = (_selectedObjIdx == i);
			if (ImGui::Selectable(_fileTextList[i].c_str(), is_selected))
				if (i != _selectedObjIdx)
					_selectedObjIdx = i;
				else
					_selectedObjIdx = -1;


			if (is_selected)
			{
				if (_selectedObjIdx >= 0)
					_mapSelectDesc = _mapInitInfoList[_selectedObjIdx];
				else
					_mapSelectDesc = nullptr;
			}
			
		}
		ImGui::EndListBox();
	}

	ImGui::End();
}

void MapManager::ChangeMapObjPosition()
{
	Vec3 position = {0.0f,0.0f,0.0f};
	float dx = INPUT->GetMouseDeltaX() * 0.01f;
	float dy = INPUT->GetMouseDeltaY() * 0.01f;
	if(_isZState)
	{
		position.z = -dy;
	}
	else
	{
		position.x = dx;
		position.y = -dy;
	}

	_mapSelectObj->GetTransform()->AddLocalPosition(position);
}

void MapManager::ChangeMapObjRotation()
{
	Vec3 rotation = { 0.0f,0.0f,0.0f };
	float dx = INPUT->GetMouseDeltaX() * 0.01;
	float dy = INPUT->GetMouseDeltaY() * 0.01;
	if (_isZState)
	{
		rotation.z = -dx;
	}
	else
	{
		rotation.x = -dy;
		rotation.y = -dx;
	}
	_mapSelectObj->GetTransform()->AddLocalRotation(rotation);
}


// TODO : 스케일값을 바꿀 때, 콜라이더도 같이 커지게 하는 기능 필요.
void MapManager::ChangeMapObjScale()
{
	Vec3 scale = { 0.0f,0.0f,0.0f };
	float dx = INPUT->GetMouseDeltaX() * 0.0001;
	float dy = INPUT->GetMouseDeltaY() * 0.0001;

	float all = dx - dy;
	scale.x = all;
	scale.y = all;
	scale.z = all;
	
	_mapSelectObj->GetTransform()->AddLocalScale(scale);
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
		dec.isCollision = (_mapObjList[i]->GetCollider() == nullptr) ? false : true;
		fwrite(&dec.isCollision, sizeof(bool), 1, fp);

		AABBBoxCollider* collider = dynamic_cast<AABBBoxCollider*>(_mapObjList[i]->GetCollider().get());
		Vec3 extents = collider->GetBoundingBox().Extents;
		dec.extent = extents;
		fwrite(&dec.extent, sizeof(Vec3), 1, fp);
		dec.offset = _mapObjList[i]->GetCollider()->GetOffset();
		fwrite(&dec.offset, sizeof(Vec3), 1, fp);

		dec.pos = _mapObjList[i]->GetTransform()->GetLocalPosition();
		fwrite(&dec.pos, sizeof(Vec3), 1, fp);
		dec.scale = _mapObjList[i]->GetTransform()->GetLocalScale();
		fwrite(&dec.scale, sizeof(Vec3), 1, fp);
		dec.rotation = _mapObjList[i]->GetTransform()->GetLocalRotation();
		fwrite(&dec.rotation, sizeof(Vec3), 1, fp);

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
		fread(&dec.isCollision, sizeof(bool), 1, fp);
		fread(&dec.extent, sizeof(Vec3), 1, fp);
		fread(&dec.offset, sizeof(Vec3), 1, fp);

		fread(&dec.pos, sizeof(Vec3), 1, fp);
		fread(&dec.scale, sizeof(Vec3), 1, fp);
		fread(&dec.rotation, sizeof(Vec3), 1, fp);

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

void MapManager::UpdateMapDescTransform()
{
	ImGui::Begin("MapDesc Inspector");


	switch (_transformSelect)
	{
	case 0:
	{
		ImGui::DragFloat("positionX", &_mapSelectDesc->pos.x, 0.1f);
		ImGui::DragFloat("positionY", &_mapSelectDesc->pos.y, 0.1f);
		ImGui::DragFloat("positionZ", &_mapSelectDesc->pos.z, 0.1f);
		break;
	}
	case 1:
	{
		ImGui::DragFloat("rotationX", &_mapSelectDesc->rotation.x, 0.1f);
		ImGui::DragFloat("rotationY", &_mapSelectDesc->rotation.y, 0.1f);
		ImGui::DragFloat("rotationZ", &_mapSelectDesc->rotation.z, 0.1f);
		break;
	}
	case 2:
	{
		ImGui::DragFloat("scaleX", &_mapSelectDesc->scale.x, 0.001f);
		ImGui::DragFloat("scaleY", &_mapSelectDesc->scale.y, 0.001f);
		ImGui::DragFloat("scaleZ", &_mapSelectDesc->scale.z, 0.001f);
		break;
	}
	case 3:
	{
		ImGui::DragFloat("colliderX", &_mapSelectDesc->extent.x, 0.1f);
		ImGui::DragFloat("colliderY", &_mapSelectDesc->extent.y, 0.1f);
		ImGui::DragFloat("colliderZ", &_mapSelectDesc->extent.z, 0.1f);
		ImGui::NewLine;
		ImGui::DragFloat("offsetX", &_mapSelectDesc->offset.x, 0.01f);
		ImGui::DragFloat("offsetY", &_mapSelectDesc->offset.y, 0.01f);
		ImGui::DragFloat("offsetZ", &_mapSelectDesc->offset.z, 0.01f);
		break;
	}
	default:
		break;
	}

	ImGui::End();

}

void MapManager::UpdateMapObjTransform()
{
	ImGui::Begin("MapObject Inspector");

	Vec3 position = _mapSelectObj->GetTransform()->GetLocalPosition();
	Vec3 rotation = _mapSelectObj->GetTransform()->GetLocalRotation();
	Vec3 scale = _mapSelectObj->GetTransform()->GetLocalScale();
	AABBBoxCollider* collider = dynamic_cast<AABBBoxCollider*>(_mapSelectObj->GetCollider().get());
	Vec3 extent = collider->GetBoundingBox().Extents;
	Vec3 offset = _mapSelectObj->GetCollider()->GetOffset();

	switch (_transformSelect)
	{
	case 0:
	{
		ImGui::DragFloat("positionX", &position.x, 0.1f);
		ImGui::DragFloat("positionY", &position.y, 0.1f);
		ImGui::DragFloat("positionZ", &position.z, 0.1f);
		_mapSelectObj->GetTransform()->SetLocalPosition(position);
		break;
	}
	case 1:
	{
		ImGui::DragFloat("rotationX", &rotation.x, 0.1f);
		ImGui::DragFloat("rotationY", &rotation.y, 0.1f);
		ImGui::DragFloat("rotationZ", &rotation.z, 0.1f);
		_mapSelectObj->GetTransform()->SetLocalRotation(rotation);
		break;
	}
	case 2:
	{
		ImGui::DragFloat("scaleX", &scale.x, 0.001f);
		ImGui::DragFloat("scaleY", &scale.y, 0.001f);
		ImGui::DragFloat("scaleZ", &scale.z, 0.001f);
		_mapSelectObj->GetTransform()->SetLocalScale(scale);
		break;
	}
	case 3:
	{
		ImGui::DragFloat("extentX", &extent.x, 0.1f);
		ImGui::DragFloat("extentY", &extent.y, 0.1f);
		ImGui::DragFloat("extentZ", &extent.z, 0.1f);
		ImGui::NewLine;
		ImGui::NewLine;
		ImGui::DragFloat("offsetX", &offset.x, 0.01f);
		ImGui::DragFloat("offsetY", &offset.y, 0.01f);
		ImGui::DragFloat("offsetZ", &offset.z, 0.01f);

		collider->GetBoundingBox().Extents = extent;
		_mapSelectObj->GetCollider()->SetOffset(offset);
		break;
	}
	default:
		break;
	}

	ImGui::End();
}

void MapManager::UpdateMapObjCollider()
{
	// 콜라이더를... 어떻게... 할까

}


// TODO : 맵 오브젝트가 단 한개도 없으면 파일에 저장되지 않음.
void MapManager::RemoveMapObj()
{
	auto it = std::find(_mapObjList.begin(), _mapObjList.end(), _mapSelectObj);

	if (it != _mapObjList.end())
	{
		_mapObjList.erase(it);
	}

	SCENE->GetCurrentScene()->Remove(_mapSelectObj);


	_mapSelectObj.reset();
}

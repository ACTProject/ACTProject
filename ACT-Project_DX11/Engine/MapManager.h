#pragma once

enum MapObjSelect
{
	START = 0
};


struct MapObjDesc
{
public:
	bool isCollision = true;
	Vec3 extent = Vec3{ 1.0f };
	Vec3 offset = Vec3{ 0.0f };
	Vec3 pos = { 0.f,0.f,0.f };
	Vec3 scale = { 0.001f,0.001f,0.001f };
	Vec3 rotation = {0.0f, 0.0f, 0.0f};
	int fileLength = 0;
	int shaderLength = 0;
	wstring filename;
	wstring shadername;
	MapObjDesc() = default;
	MapObjDesc(wstring file, wstring sha, bool isColl = true) : filename(file), shadername(sha), isCollision(isColl) {};
};

class MapManager
{
	DECLARE_SINGLE(MapManager);
public:
	void Init();
	void Update();
	bool ChekMapDescSelect() { return  _mapSelectDesc == nullptr; };
	bool ChekMapObj() { return _mapSelectObj != nullptr; };
	bool ChekMapObjectSelect(shared_ptr<GameObject> obj);

	// 이 함수는 클릭했을 때 추가하는 함수.
	shared_ptr<GameObject> Create(Vec3& pos);


	// 초기 init
	void AddMapObj(shared_ptr<MapObjDesc>  obj);
	void InitMapText();

	// 파일에 맵 오브젝트 정보 추가하는 함수
	bool ExportMapObj();
	// 파일을 읽어 들이는 함수
	bool ImportMapObj();
private:
	// 클릭하지 않고도 맵오브젝트 설치 전에 보이게끔 하는 함수.
	void PreViewMapObject();
	shared_ptr<GameObject> CreatePreViewObj(Vec3 pickPos);

	void UpdateMapDescTransform();
	void UpdateMapObjTransform();
	void RemoveMapObj(shared_ptr<GameObject> obj);

	void ChangeMapObjPosition();
	void ChangeMapObjRotation();
	void ChangeMapObjScale();

	// 이 함수는 파일에서 불러올 때 사용하는 함수
	shared_ptr<GameObject> Create(MapObjDesc& obj);
	// ImGui에서 맵오브젝트 고르는 함수.
	void ImGuiSelectMapObject();
private:
	// 정보 저장된 파일이름.
	wstring _fileName = L"../Resources/MapObj/MapObjectLists.txt";
	// 파일로 저장시킬 오브젝트들 리스트
	vector<shared_ptr<GameObject>> _mapObjList;
	// 맵정보 구조체 배열
	vector<shared_ptr<MapObjDesc>> _mapInfoList;
	// 초기 맵 정보 구조체 배열.
	vector<shared_ptr<MapObjDesc>> _mapInitInfoList;
	shared_ptr<MapObjDesc> _mapSelectDesc;
	shared_ptr<GameObject> _mapSelectObj;
	shared_ptr<GameObject> _mapPreviewObj;

	Vec3 _pickPos;
	vector<string> _fileTextList;
	int _selectedObjIdx = -1;
	int _transformSelect = 0;
	bool _isZState = false;
	bool _isSelect = false;
};
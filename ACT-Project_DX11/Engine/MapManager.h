#pragma once

enum MapObjSelect
{
	START = 0
};


struct MapObjDesc
{
public:
	Vec3 pos = { 0.f,0.f,0.f };
	Vec3 scale = { 0.001f,0.001f,0.001f };
	int fileLength = 0;
	int shaderLength = 0;
	wstring filename;
	wstring shadername;
	MapObjDesc() = default;
	MapObjDesc(wstring file, wstring sha) : filename(file), shadername(sha) {};
	MapObjDesc(wstring file, wstring sha, Vec3 scal) : filename(file), shadername(sha), scale(scal) {};
};

class MapManager
{
	DECLARE_SINGLE(MapManager);
public:
	void Init();
	bool ChekMapObjSelect() { return _selectObject != nullptr; };
	void Update();
	// 이 함수는 클릭했을 때 추가하는 함수.
	shared_ptr<GameObject> Create(Vec3& pos);
	// 이 함수는 파일에서 불러올 때 사용하는 함수
	shared_ptr<GameObject> Create(MapObjDesc& obj);
	// 초기 init
	void AddMapObj(shared_ptr<MapObjDesc>  obj);

	// 파일에 맵 오브젝트 정보 추가하는 함수
	bool ExportMapObj();
	// 파일을 읽어 들이는 함수
	bool ImportMapObj();
private:
	// 정보 저장된 파일이름.
	wstring _fileName = L"../Resources/MapObj/MapObjectLists.txt";
	// 파일로 저장시킬 오브젝트들 리스트
	vector<shared_ptr<GameObject>> _mapObjList;
	// 맵정보 구조체 배열
	vector<shared_ptr<MapObjDesc>> _mapInfoList;
	shared_ptr<MapObjDesc> _selectObject;
};
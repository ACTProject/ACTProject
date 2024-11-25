#pragma once


class Client : public IExecute
{
public:
	void Init() override;
	void Update() override;
	void Render() override;

private:
	shared_ptr<GameObject> terrainObj;

	vector<vector<uint8>> CreateMinimapLevels(uint8* heightMapData, int width, int height, int lodLevels);
	vector<VertexTextureNormalTangentData> GenerateLODVertices(const vector<uint8>& minimap, int lodWidth, int lodHeight, int maxHeight);
	vector<uint32> GenerateLODIndices(int lodWidth, int lodHeight);
};
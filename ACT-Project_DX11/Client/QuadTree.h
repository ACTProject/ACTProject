#pragma once

struct QuadTreeNode {
    int startX, startZ; // 노드의 시작 좌표
    int size;           // 노드가 담당하는 영역의 크기
    std::vector<int> indices; // 인덱스 데이터
    QuadTreeNode* children[4] = { nullptr, nullptr, nullptr, nullptr }; // 자식 노드
};

class QuadTree {
public:
    QuadTree(const std::vector<VertexTextureNormalTangentData>& vertices, int terrainWidth, int terrainHeight)
        : vertices(vertices), terrainWidth(terrainWidth), terrainHeight(terrainHeight) {}

    void Build(int startX, int startZ, int size);
    void Render(QuadTreeNode* node, const Vec3& cameraPosition, float detailDistance, std::vector<uint32_t>& outIndices);


    QuadTreeNode* GetRoot() { return root; }

    void SetRoot(QuadTreeNode* root) { this->root = root; }

private:
    const std::vector<VertexTextureNormalTangentData>& vertices;
    int terrainWidth;
    int terrainHeight;
    QuadTreeNode* root = nullptr;

    void BuildRecursive(int startX, int startZ, int size, QuadTreeNode*& node);
    void Clear(QuadTreeNode* node);
};

#include "pch.h"
#include "QuadTree.h"

void QuadTree::Build(int startX, int startZ, int size) {
    root = new QuadTreeNode();
    BuildRecursive(startX, startZ, size, root);
}

void QuadTree::Render(QuadTreeNode* node, const Vec3& cameraPosition, float detailDistance, std::vector<uint32>& outIndices) {
    if (!node) return;

    // 노드 중심과 카메라 간 거리 계산
    Vec3 nodeCenter = Vec3(node->startX + node->size / 2.0f, 0, node->startZ + node->size / 2.0f);
    float distance = (cameraPosition - nodeCenter).Length();

    // 디테일 거리보다 가까운 경우 현재 노드의 인덱스를 사용
    if (distance <= detailDistance || node->children[0] == nullptr) {
        // 현재 노드의 삼각형 인덱스를 추가
        outIndices.insert(outIndices.end(), node->indices.begin(), node->indices.end());
    }
    else {
        // 자식 노드 탐색
        for (int i = 0; i < 4; ++i) {
            Render(node->children[i], cameraPosition, detailDistance, outIndices);
        }
    }

}

void QuadTree::BuildRecursive(int startX, int startZ, int size, QuadTreeNode*& node)
{
    node->startX = startX;
    node->startZ = startZ;
    node->size = size;

    if (size == 1) {
        // Leaf 노드: 삼각형 인덱스 생성
        int topLeft = startZ * terrainWidth + startX;
        int topRight = startZ * terrainWidth + (startX + 1);
        int bottomLeft = (startZ + 1) * terrainWidth + startX;
        int bottomRight = (startZ + 1) * terrainWidth + (startX + 1);

        node->indices.push_back(topLeft);
        node->indices.push_back(bottomLeft);
        node->indices.push_back(topRight);

        node->indices.push_back(topRight);
        node->indices.push_back(bottomLeft);
        node->indices.push_back(bottomRight);
    }
    else {
        // 내부 노드: 자식 노드 생성
        int halfSize = size / 2;

        node->children[0] = new QuadTreeNode();
        BuildRecursive(startX, startZ, halfSize, node->children[0]);

        node->children[1] = new QuadTreeNode();
        BuildRecursive(startX + halfSize, startZ, halfSize, node->children[1]);

        node->children[2] = new QuadTreeNode();
        BuildRecursive(startX, startZ + halfSize, halfSize, node->children[2]);

        node->children[3] = new QuadTreeNode();
        BuildRecursive(startX + halfSize, startZ + halfSize, halfSize, node->children[3]);
    }
}

void QuadTree::Clear(QuadTreeNode* node)
{
    if (!node) return;

    for (int i = 0; i < 4; ++i) {
        if (node->children[i]) {
            Clear(node->children[i]);
            delete node->children[i];
            node->children[i] = nullptr;
        }
    }
    delete node;//
}

#include "huffman.h"

using namespace std;

Huffman::Huffman(void) {
    huffmanTreeRoot = nullptr;
}

Huffman::~Huffman(void) {
    if (huffmanTreeRoot == nullptr)
        return;
    queue<TreeNode*> q;
    q.push(huffmanTreeRoot);
    while (!q.empty()) {
        TreeNode* node  = q.front();
        q.pop();
        if (node -> left != nullptr)
            q.push(node -> left);
        if (node -> right != nullptr)
            q.push(node -> right);
        delete(node);
    }
    huffmanTreeRoot = nullptr;
}

void Huffman::buildWeightMap(const short* dataPtr, uint32_t dataSize, unordered_map<short, uint32_t>& weightMap) {
    for (uint32_t i = 0; i < dataSize; i++) {
        weightMap[dataPtr[i]]++;
    }
}

void Huffman::buildHuffmanTree(const unordered_map<short, uint32_t> &weightMap) {
    // 迭代器遍历权值map，将数和对应的权值构建成节点传入队列
    for (const auto &iter : weightMap) {
        nodeQueue.push(new TreeNode(iter.first, iter.second));
    }

    // 由于nodeQueue会按照权值由到大排序，一次出栈两个节点， 
    // 这两个节点肯定是权值最小的两个节点，由这两个节点构成一个树，
    // 该树的权值为nodeQueue取出权值之和，将该树的根节点传入队列
    // 次数队列重新排序，再次循环取前两个节点计算，直到队列的所有节点被构成一个树
    while (nodeQueue.size() > 1) {
        TreeNode* rightNode = nodeQueue.top();
        nodeQueue.pop();
        TreeNode* leftNode = nodeQueue.top();
        nodeQueue.pop();
        auto parentNode = new TreeNode(0, rightNode -> weight + leftNode -> weight);
        parentNode -> left = leftNode;
        parentNode -> right = rightNode;
        nodeQueue.push(parentNode);
    }

    // 最终哈夫曼树的根节点
    huffmanTreeRoot = nodeQueue.top();
}

void print_hello()
{
    printf("hello");
}
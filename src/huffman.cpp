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
    /** The iterator traverses the weight map, passing the values and weights into the queue as nodes */
    for (const auto &iter : weightMap) {
        nodeQueue.push(new TreeNode(iter.first, iter.second));
    }

    /** 
     * The node queues are arranged from small to large by weight, 
     * and then two nodes are taken out to synthesize the new nodes, 
     * and then the new nodes are sorted into the queue until all nodes form a Huffman tree.
     */
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

    huffmanTreeRoot = nodeQueue.top();
}

void Huffman::DFSTree(TreeNode* treeNode, HuffmanCode& tempCode, unordered_map<short, HuffmanCode> &huffmanCodeMap) {
    /** Traverse to the leaf node and match the leaf node value to the encoding. */
    if (treeNode -> left == nullptr && treeNode -> right == nullptr) {
        huffmanCodeMap[treeNode -> val] = tempCode;
        return;
    }

    tempCode.push(0);
    DFSTree(treeNode -> left, tempCode, huffmanCodeMap);
    tempCode.pop();
    tempCode.push(1);
    DFSTree(treeNode -> right, tempCode, huffmanCodeMap);
    tempCode.pop();
}

void Huffman::buildHuffmanCodeMap(unordered_map<short, HuffmanCode> &huffmanCodeMap) {
    if (huffmanTreeRoot == nullptr)
        return;
    
    HuffmanCode tempCode;
    DFSTree(huffmanTreeRoot, tempCode, huffmanCodeMap);
}

uint32_t Huffman::getEncoderBitSize(const unordered_map<short, uint32_t> &weightMap, const unordered_map<short, HuffmanCode> &huffmanCodeMap) {
    short value;
    uint32_t weight;
    uint32_t oneCodeLen;
    uint32_t totalCodeLen = 0;

    for (const auto &iter : weightMap) {
        value = iter.first;
        weight = iter.second;
        oneCodeLen = static_cast<uint32_t >(huffmanCodeMap.at(value).getLen());
        totalCodeLen += weight * oneCodeLen;
    }

    return totalCodeLen;
}
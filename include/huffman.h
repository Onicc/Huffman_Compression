#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <cstdio>
#include <string>
#include <queue>
#include <unordered_map>

#include "huffmanCode.h"

using namespace std;

void print_hello();

class Huffman {
    private:
        struct TreeNode {
            short val;
            uint32_t weight;
            TreeNode *left;
            TreeNode *right;
            TreeNode(short _val, uint32_t _weight) : val(_val), weight(_weight), left(nullptr), right(nullptr) {}
        };

        struct nodePtrCmp {
            bool operator() (TreeNode* a, TreeNode* b) {
                return (a -> weight) >= (b -> weight);
            }
        };

        // 队列中存放树节点，并且按照权值由小到大排列
        priority_queue<TreeNode*, vector<TreeNode*>, nodePtrCmp> nodeQueue;

    public:
        Huffman(void);
        ~Huffman(void);

        // 最终编码好的哈夫曼数的根节点，由这个节点可以便利任一节点
        TreeNode *huffmanTreeRoot;

        void buildWeightMap(const short* dataPtr, uint32_t dataSize, unordered_map<short, uint32_t>& weightMap);
        void buildHuffmanTree(const unordered_map<short, uint32_t> &weightMap);
        void DFSTree(TreeNode* treeNode, HuffmanCode& tempCode, unordered_map<short, HuffmanCode> &huffmanCodeMap);
        void buildHuffmanCode(unordered_map<short, HuffmanCode> &huffmanCodeMap);
};

#endif
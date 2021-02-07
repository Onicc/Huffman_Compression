#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <cstdio>
#include <string>
#include <queue>
#include <unordered_map>

#include "huffmanCode.h"

using namespace std;

class Huffman {
    private:
        struct TreeNode {
            short val;
            uint32_t weight;
            TreeNode *left;
            TreeNode *right;
            TreeNode(short _val, uint32_t _weight) : val(_val), weight(_weight), left(nullptr), right(nullptr) {}
        };

        /** Comparison rules: Sort by weight from small to large. */
        struct nodePtrCmpare {
            bool operator() (TreeNode* a, TreeNode* b) {
                return (a -> weight) >= (b -> weight);
            }
        };

        /** The sorted node queue */
        priority_queue<TreeNode*, vector<TreeNode*>, nodePtrCmpare> nodeQueue;

    public:
        Huffman(void);
        ~Huffman(void);

        /** The root node of the eventual Huffman tree. */
        TreeNode *huffmanTreeRoot;

        void buildWeightMap(const short* dataPtr, uint32_t dataSize, unordered_map<short, uint32_t>& weightMap);
        void buildHuffmanTree(const unordered_map<short, uint32_t> &weightMap);
        void DFSTree(TreeNode* treeNode, HuffmanCode& tempCode, unordered_map<short, HuffmanCode> &huffmanCodeMap);
        void buildHuffmanCode(unordered_map<short, HuffmanCode> &huffmanCodeMap);
};

#endif
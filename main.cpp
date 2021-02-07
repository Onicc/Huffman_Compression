#include <cstdio>
#include <string>
#include <iostream>
#include <bitset>
#include "huffman.h"
#include "exception.h"

using namespace std;

int main()
{
    string filename = "E:/Track/Compress/frame-short-37059.data";
    FILE* fp = fopen(filename.c_str(), "rb");
    if (fp == nullptr) {
        throw MyException("Failed to open file");
    }

    int frameSize = 72*72*37059;
    auto frameDataPtr = new short[frameSize];
    unordered_map <short, uint32_t> weightMap;
    fread(frameDataPtr, sizeof(short), frameSize, fp);
    fclose(fp);

    Huffman encoder;
    encoder.buildWeightMap(frameDataPtr, frameSize, weightMap);
    encoder.buildHuffmanTree(weightMap);
    unordered_map<short, HuffmanCode> huffmanCodeMap;
    encoder.buildHuffmanCodeMap(huffmanCodeMap);

    for (const auto &iter : weightMap) {
        cout << iter.first << " " << iter.second << endl;
    }
    cout << encoder.huffmanTreeRoot->weight << endl;

    cout << "encoder" << endl;
    for (const auto &iter : huffmanCodeMap) {
        cout << iter.first << " " << bitset<8>(iter.second.getByteData()[1]) << bitset<8>(iter.second.getByteData()[0]) \
        << " " << iter.second.getLen() << endl;
    }
    // 10,368
    // 1207
    // 11.64%
    cout << "total:" << encoder.getEncoderBitSize(weightMap, huffmanCodeMap) << endl;

    return 0;
}
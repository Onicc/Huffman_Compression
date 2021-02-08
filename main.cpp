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

    int dataSize = 72*72*10;
    auto dataPtr = new short[dataSize];
    fread(dataPtr, sizeof(short), dataSize, fp);
    fclose(fp);

    Huffman encoder;
    encoder.encode(dataPtr, dataSize);

    return 0;
}
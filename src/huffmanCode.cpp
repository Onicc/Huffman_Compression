#include <cmath>
#include <cstring>
#include "exception.h"
#include "huffmanCode.h"

using namespace std;

HuffmanCode::HuffmanCode() {
    len = 0;
    byteNum = 16;
    blockNum = pow(2, 16) / 8;
    byteData = new unsigned char[blockNum];
    memset(byteData, 0, blockNum);
}

HuffmanCode::HuffmanCode(const HuffmanCode &huffmanCode) {
    len = huffmanCode.getLen();
    blockNum = huffmanCode.getBlockNum();
    byteData = new unsigned char[blockNum];
    memcpy(byteData, huffmanCode.getByteData(), blockNum);
}

HuffmanCode::~HuffmanCode() {
    delete[] byteData;
}

uint32_t HuffmanCode::getLen(void) const {
    return len;
}

uint32_t HuffmanCode::getBlockNum(void) const {
    return blockNum;
}

unsigned char *HuffmanCode::getByteData(void) const {
    return byteData;
}

void HuffmanCode::push(unsigned char bitValue) {
    if (len >= blockNum * 8)
        throw MyException("HuffmanCode::append error: Data overflow");

    uint32_t byteOff = len / 8;
    uint32_t bitOff = len % 8;
    if (bitValue & 1)
        byteData[byteOff] |= (1 << bitOff);
    else
        byteData[byteOff] &= (~(1 << bitOff));
    len++;
}

void HuffmanCode::pop(void) {
    if (len <= 0) {
        throw MyException("HuffmanCode::append error: Data underflow");
    }
    len--;
}

bool HuffmanCode::operator[](uint32_t pos) const {
    if (pos >= len) {
        throw runtime_error("HuffmanCode::[] error: access overflow");
    }
    if (pos < 0) {
        throw runtime_error("HuffmanCode::[] error: access underflow");
    }
    uint32_t byteOff = pos / 8;
    uint32_t bitOff = pos % 8;
    bool res = static_cast<bool>((byteData[byteOff] >> bitOff) & 1);
    return res;
}

HuffmanCode& HuffmanCode::operator=(const HuffmanCode &huffmanCode) {
    len = huffmanCode.getLen();
    blockNum = huffmanCode.getBlockNum();
    byteData = new unsigned char[blockNum];
    memcpy(byteData, huffmanCode.getByteData(), blockNum);
    return *this;
}
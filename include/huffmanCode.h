#ifndef HUFFMANCODE_H
#define HUFFMANCODE_H

#include <string>

using namespace std;

class HuffmanCode {
    private:
        uint32_t len;
        uint32_t byteNum;
        uint32_t blockNum;
        unsigned char *byteData;

    public:
        HuffmanCode();
        HuffmanCode(const HuffmanCode &huffmanCode);
        ~HuffmanCode();

        uint32_t getLen(void) const;
        uint32_t getBlockNum(void) const;
        unsigned char *getByteData(void) const;
        void push(unsigned char bitValue);
        void pop(void);

        bool operator[] (uint32_t pos) const;
        HuffmanCode& operator=(const HuffmanCode &huffmanCode);
};

#endif

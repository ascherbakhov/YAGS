//
// Created by qazer on 10.04.2019.
//

#ifndef NETWORK_INPUTBITSTREAM_H
#define NETWORK_INPUTBITSTREAM_H

#include <string>
#include <cstring>
#include "../utils/Constants.h"



class InputBitStream {
private:
    bufflen_t mHead;
    byte* mBuffer;


    void ReadBits(byte &data, bufflen_t size);
    void ReadBits(void* data, bufflen_t size);

public:
    explicit InputBitStream(const byte* buffer, bufflen_t size): mHead(0)
    {
        int byteCount = (size % BITS_PER_BYTE == 0) ? (size >> BYTE_SHIFT) : ((size >> BYTE_SHIFT) + 1);
        mBuffer = static_cast<byte*>(malloc(byteCount));
        memcpy(mBuffer, buffer, byteCount);
    }
    ~InputBitStream(){ std::free(mBuffer); }

    template <class T>
    void Read(T& data, bufflen_t size = sizeof(T) * BITS_PER_BYTE)
    {
        static_assert(std::is_arithmetic<T>::value || std::is_enum<T>::value,
                      "Generic BitStream::Read supports only arithmetic or enum types");
        ReadBits(&data, size);
    };
    void Read(bool& data)  { ReadBits(&data, 1); }
    void Read(std::string& inStr);
};


#endif //NETWORK_INPUTBITSTREAM_H

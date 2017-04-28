#ifndef _entropy_h_
#define _entropy_h_

#include <math.h>
#ifdef QT_CORE_LIB
#include <QVector>
#else
#include <Windows.h>
#include <vector>
#endif

#include "macro.h"

typedef double EntropyType;

class Entropy
{
private:
    EntropyType _value;
    size_t _size;
    EntropyType _calc_entropy(unsigned char *pData, size_t DataSz);
    size_t statistics[0x100];
public:
    Entropy(unsigned char *pData, size_t DataSz);
    EntropyType value() { return _value; }
	__declspec(property(
                   get = value))
    EntropyType Value;
    size_t frame_size() { return _size; }
    __declspec(property(
                   get = frame_size))
    size_t Size;
    EntropyType append_byte(unsigned char val);
    EntropyType reduce_byte(unsigned char val);
};

typedef double EntropyPoint;//TODO: make pair
#ifdef QT_CORE_LIB
typedef QVector<EntropyPoint> EntropyDiagram;
#else
typedef std::vector<EntropyPoint> EntropyDiagram;
#endif

#endif

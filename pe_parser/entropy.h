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

typedef double EntropyX, EntropyY;
typedef struct EntropyCharacteristics {
    EntropyY entropy_value;
    EntropyY entropy_derivative_value;
    EntropyY extremums_density;
} EntropyChars, EntropyPoint;

enum EntropyDirection { edirMax = -1, edirNo = 0, edirMin = 1 };

inline EntropyDirection e_sign(const EntropyType c_val) {
    return ((c_val < 0) ? edirMax : ((c_val > 0) ? edirMin : edirNo));
}

inline EntropyDirection e_dir(const EntropyY prev, const EntropyY cur) {
    if(prev * cur < 0)
        return e_sign(cur - prev);
    else
        return edirNo;
}

#ifdef QT_CORE_LIB
typedef QVector<EntropyPoint> EntropyDiagram;
//typedef QVector<ExtremumDensityPoint> ExtremumDensityDiagram;
typedef struct ExtremumPoint {
    EntropyX X;
    EntropyDirection eDir;
    ExtremumPoint(EntropyX x = 0.,
                  EntropyDirection edir = edirNo) : X(x),
        eDir(edir)
    {}
} *PExtremumPoint;

typedef QVector<ExtremumPoint> ExtremumPoints;

#else
typedef std::vector<EntropyPoint> EntropyDiagram;
typedef std::vector<ExtremumDensityPoint> ExtremumDensityDiagram;
#endif

#endif

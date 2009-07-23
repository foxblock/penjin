#ifndef NUMBERUTILITY_H_INCLUDED
#define NUMBERUTILITY_H_INCLUDED
#include <cmath>
#include "PenjinTypes.h"

namespace NumberUtility
{
#ifdef PENJIN_FIXED
    Fixed linearInterpolate(CRint x, CRint y, CRFixed step);
    int roundUp(CRFixed x);
    int roundDown(CRFixed x);
#else
    float linearInterpolate(CRint x, CRint y, CRfloat step);
    int roundUp(CRfloat x);
    int roundDown(CRfloat x);
#endif
    template <class T>
    T min(const T& a, const T& b){return a<b ? a : b;}
    template <class T>
    T max(const T& a, const T& b){return a>b ? a : b;}
    template <class T>
    T limit(const T& x, const T& minV, const T& maxV){return min( maxV, max(minV,x));}
    bool isMultiple(CRint x,CRint y);
    int nextPowerOfTwo(CRint x);
    // Check if a value is a power of two
    bool isPowerOfTwo(CRint x);
    int wrapValue(int value, CRint limit);

//        template<typename T>
//        T wrapValue(T val,const T& limit);
}
#endif // NUMBERUTILITY_H_INCLUDED

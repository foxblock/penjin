#ifndef NUMBERUTILITY_H_INCLUDED
#define NUMBERUTILITY_H_INCLUDED

#include "PenjinTypes.h"

namespace NumberUtility
{
    /// analysis

#ifdef PENJIN_FIXED
    Fixed linearInterpolate(CRint x, CRint y, CRFixed step);
#else
    float linearInterpolate(CRint x, CRint y, CRfloat step);
#endif

    template <class T>
    T limit(const T& x, const T& minV, const T& maxV){return min( maxV, max(minV,x));}
    bool isMultiple(CRint x,CRint y);
    bool isPowerOfTwo(CRint x);
    bool isPrime(CRuint value);
    int nextPowerOfTwo(CRint x);
    template <class T>
    int sign(const T& value);   // Signum function, returns the sign of a number
    int wrapValue(int value, CRint limit);
    //template<typename T>
    //T wrapValue(T val,const T& limit);

    /// statistics

    int getGreatest(const int arr[], CRuint length);                    // Returns the greatest number in an array
    int getGreatestIndex(const int arr[], CRuint length);               // Returns the index of the greatest number in an array
    bool isGreatest(const int arr[], CRuint index, CRuint length);       // Checks if the supplied element is the greatest in an array of numbers
    //template <class T, int length>
    //T test(const T (&arr)[length], CRint index);

};
#endif // NUMBERUTILITY_H_INCLUDED

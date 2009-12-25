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

    int digitSum(CRuint value);
    double fact(CRuint value);  // Returns the factorial of a given value (limit is 170)
    template <class T, size_t length>
    size_t getSize(const T (&arr)[length]){return length;} // Get the size of any array (array type must not have private data members)
    bool isEven(CRint value);
    bool isMultiple(CRint x,CRint y);
    bool isOdd(CRint value);
    bool isPowerOfTwo(CRint x);
    bool isPrime(CRuint value);
    template <class T>
    T limit(const T& x, const T& minV, const T& maxV){return min( maxV, max(minV,x));}
    int nextPowerOfTwo(CRint x);
    template <class T>
    int sign(const T& value); // Signum function, returns the sign of a number
    int wrapValue(int value, CRint limit);
    //template<typename T>
    //T wrapValue(T val,const T& limit);

    /// statistics / arrays
    template <class T, int length>
    T getGreatest(const T (&arr)[length]); // Returns the greatest number in an array
    template <class T, int length>
    int getGreatestIndex(const T (&arr)[length]); // Returns the index of the greatest number in an array
    template <class T, int length>
    bool isGreatest(const T (&arr)[length], CRuint index); // Checks if the supplied element is the greatest in an array of numbers

    /// Angles
    float degToRad(CRfloat a);
    float radToDeg(CRfloat a);
};

#include "NumberUtility.inl"

#endif // NUMBERUTILITY_H_INCLUDED

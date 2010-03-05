#ifndef NUMBERUTILITY_H_INCLUDED
#define NUMBERUTILITY_H_INCLUDED

#include "PenjinTypes.h"

#define M_PI 3.141592653f

namespace NumberUtility
{
    /// Analysis

#ifdef PENJIN_FIXED
    Fixed linearInterpolate(CRint x, CRint y, CRFixed step);
#else
    float linearInterpolate(CRint x, CRint y, CRfloat step);
#endif

    int digitSum(CRuint value);
    double fact(CRuint value);  // Returns the factorial of a given value: x! (limit is 170)
    bool isEven(CRint value);
    bool isMultiple(CRint x,CRint y);
    bool isOdd(CRint value);
    bool isPowerOfTwo(CRint x);
    bool isPrime(CRuint value);
    template <class T>
    T limit(const T& x, const T& minV, const T& maxV){return min( maxV, max(minV,x));}
    int nextPowerOfTwo(CRint x);
    template <class T>
    int sign(const T& value); // Signum function, returns the sign of a number (-1 for negative numbers, 1 for positive ones, 0 for 0)
    int wrapValue(int value, CRint limit);
    //template<typename T>
    //T wrapValue(T val,const T& limit);

    /// Angles
    float degToRad(CRfloat a);
    float radToDeg(CRfloat a);

    /// Statistics
    template <class T, int length>
    T getGreatest(const T (&arr)[length]); // Returns the greatest number in an array
    template <class T, int length>
    int getGreatestIndex(const T (&arr)[length]); // Returns the index of the greatest number in an array
    template <class T, int length>
    bool isGreatest(const T (&arr)[length], CRuint index); // Checks if the supplied element is the greatest in an array of numbers
    template <class T, int length>
    T getLowest(const T (&arr)[length]); // Returns the lowest number in an array
    template <class T, int length>
    int getLowestIndex(const T (&arr)[length]); // Returns the index of the lowest number in an array
    template <class T, int length>
    bool isLowest(const T (&arr)[length], CRuint index); // Checks if the supplied element is the lowest in an array of numbers

    /// Arrays
    template <class T, size_t length>
    size_t getSize(const T (&arr)[length]){return length;} // Get the size of any array (array type must not have private data members)
    template <class T, int length>
    void insert(T (&arr)[length], CRint pos, T value); // Inserst a value at a position in an array - make sure the array is already big enough to hold the new value
    template <class T, int length>
    void sort(const T (&arr)[length], int (&sortIndex)[length], CRbool ascending); // Returns an array containing the indices of the elements sorted - NOT optimized for speed
};

#include "NumberUtility.inl"

#endif // NUMBERUTILITY_H_INCLUDED
#include "NumberUtility.h"

///----------------------
/// analysis
///----------------------

#ifdef PENJIN_FIXED
    Fixed NumberUtility::linearInterpolate(CRint x, CRint y, CRFixed step)
    {
        Fixed temp = x + step;
        if(temp < y)
            return temp;
        return Fixed(y);
    }
#else
    float NumberUtility::linearInterpolate(CRint x, CRint y, CRfloat step)
    {
        float temp = x + step;
        if(temp < y)
            return temp;
        return (float)y;
    }
#endif

int NumberUtility::nextPowerOfTwo(CRint x)
{
    double logbase2 = log(x) / log(2);
    return (int)round(pow(2,ceil(logbase2)));
}

bool NumberUtility::isPowerOfTwo(CRint x){return ((x != 0) && !(x & (x - 1)));}

bool NumberUtility::isPrime(CRuint value)
{
    for (int I = 2; I <= int(value/2); I++)
        if (value % I == 0)
            return false;
    return true;
}

bool NumberUtility::isMultiple(CRint x,CRint y){return (x%y == 0);}

template <class T>
int NumberUtility::sign(const T& value)
{
    if (value == 0)
        return 0;
    else
        return value / abs(value);
}

int NumberUtility::wrapValue(int val,CRint limit)
{
    //  We need to keep going until it is within the required range.
    while(val < 0 && val >limit)
    {
    //  We can't have it less than 0, as it causes problems.
        if(val < 0)
        {
    //  compensate upwards
            val += limit;
        }
    //  We can't have it more than the limit either
        else if(val > limit)
        {
    //  compensate downwards
            val -= limit;
        }
    }
    return val;
}

//template<typename T>
//T NumberUtility::wrapValue(T val,const T& limit)
//{
////    	We need to keep going until it is within the required range.
//    while(val < 0 && val >limit)
//    {
////        	We can't have it less than 0, as it causes problems.
//        if(val < 0)
//        {
////             compensate upwards
//            val += limit;
//        }
////        	We can't have it more than the limit either
//        else if(val > limit)
//        {
////            	compensate downwards
//            val -= limit;
//        }
//    }
//    return val;
//}


///----------------------
/// statistics
///----------------------

int NumberUtility::getGreatest(const int arr[], CRuint length)
{
    int result = arr[0];
    for (int I = 1; I < length; I++)
    {
        if (arr[I] > result)
        {
            result = arr[I];
        }
    }
    return result;
}

int NumberUtility::getGreatestIndex(const int arr[], CRuint length)
{
    int result = 0;
    for (int I = 1; I < length; I++)
    {
        if (arr[I] > arr[result])
        {
            result = I;
        }
    }
    return result;
}

bool NumberUtility::isGreatest(const int arr[], CRuint index, CRuint length)
{
    for (int I = 0; I < length; I++)
    {
        if (arr[I] > arr[index])
        {
            return false;
        }
    }
    return true;
}

/*template <class T, int length>
T NumberUtility::test(const T (&arr)[length], CRint index)
{
    return arr[index];
}*/

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

int NumberUtility::digitSum(CRint value)
{
    int result = 0;
    int temp = value;
    while (temp != 0)
        {
            result += temp % 10;
            temp /= 10;
        }
    return result;
}

bool NumberUtility::isEven(CRint value){return (value%2 == 0);}

bool NumberUtility::isMultiple(CRint x,CRint y){return (x%y == 0);}

bool NumberUtility::isOdd(CRint value){return !(value%2 ==0);}

bool NumberUtility::isPowerOfTwo(CRint x){return ((x != 0) && !(x & (x - 1)));}

int NumberUtility::nextPowerOfTwo(CRint x)
{
    double logbase2 = log(x) / log(2);
    return (int)round(pow(2,ceil(logbase2)));
}

bool NumberUtility::isPrime(CRuint value)
{
    for (int I = 2; I <= int(value/2); I++)
        if (value % I == 0)
            return false;
    return true;
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

float NumberUtility::degToRad(CRfloat a)
{
    return a * 0.017453292f;
}

float NumberUtility::radToDeg(CRfloat a)
{
    return a * 57.29578f;
}

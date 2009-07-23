#include "NumberUtility.h"

#ifdef PENJIN_FIXED
    Fixed NumberUtility::linearInterpolate(CRint x, CRint y, CRFixed step)
    {
        Fixed temp = x + step;
        if(temp < y)
            return temp;
        return Fixed(y);
    }
    int NumberUtility::roundUp(CRFixed x){return Fixed(x + 0.5f).intValue<<16;}
    int NumberUtility::roundDown(CRFixed x){return Fixed(x - 0.5f).intValue<<16;}
#else
    float NumberUtility::linearInterpolate(CRint x, CRint y, CRfloat step)
    {
        float temp = x + step;
        if(temp < y)
            return temp;
        return (float)y;
    }
    int NumberUtility::roundUp(CRfloat x){return (int)(x + 0.5f);}
    int NumberUtility::roundDown(CRfloat x){return (int)(x - 0.5f);}
#endif

int NumberUtility::nextPowerOfTwo(CRint x)
{
    double logbase2 = log(x) / log(2);
    return (int)round(pow(2,ceil(logbase2)));
}

/// Check if a value is a power of two
bool NumberUtility::isPowerOfTwo(CRint x){return ((x != 0) && !(x & (x - 1)));}

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


bool NumberUtility::isMultiple(CRint x,CRint y){return (x%y == 0);}

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

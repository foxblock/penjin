#include "LUT.h"

namespace LUT
{
    /// Variables
    const float FIXED_PI = PI;  //Should work for PENJIN_FIXED
    float* sinCos;
    float* tanTable;
}

void LUT::init()
{
    sinCos = tanTable = NULL;
    sinCos = new float[128];    //  floats will be swapped to fixed types with the #define PENJIN_FIXED
    tanTable = new float[128];
    for(uint i = 0; i < 128; ++i)
    {
        //  1/256 = 0.00390625f
        #ifdef PENJIN_FIXED
            sinCos[i] = sin(fixedpoint::fix2float(i * (2*PI)*ONE_OVER_TWOFIVESIX));
            tanTable[i] = tan(fixedpoint::fix2float(i * (2*PI)*ONE_OVER_TWOFIVESIX));
        #else
            sinCos[i] = sin(i * (2*PI)*ONE_OVER_TWOFIVESIX);
            tanTable[i] = tan(i * (2*PI)*ONE_OVER_TWOFIVESIX);
        #endif
    }

}

void LUT::deInit()
{
    if(sinCos)
    {
        delete [] sinCos;
        sinCos = NULL;
    }
    if(tanTable)
    {
        delete [] tanTable;
        tanTable = NULL;
    }
}

float LUT::Lsin(uchar angle)
{
    //  Wrapping should be done automatically for us due to storage limits of uchar
    if(angle > 128)
    {
        angle-=128;
        return -(sinCos[angle]);    //  Values are mirrored just negative so we just nagate
    }
    return sinCos[angle];
}

float LUT::Lcos(CRuchar angle){return Lsin(angle+64);}

float LUT::Ltan(uchar angle)
{
    if(angle > 128)
    {
        angle-=128;
        return -(tanTable[angle]);
    }
    return tanTable[angle];
}

/// Interpolated Trig functions
//  CAUTION will not be accurate...
float LUT::LIsin(float angle)
{
    float x1 = floor(angle*1000*ONE_OVER_PI);
    float y1 = Lsin(x1);
    float y2 = Lsin(x1+1);
    return y1 + (y2-y1)*(angle*1000/PI-x1);
}

float LUT::LIcos(float angle)
{
    float x1 = floor(angle*1000*ONE_OVER_PI);
    float y1 = Lcos(x1);
    float y2 = Lcos(x1+1);
    return y1 + (y2-y1)*(angle*1000/PI-x1);
}

float LUT::LItan(float angle)
{
    float x1 = floor(angle*1000*ONE_OVER_PI);
    float y1 = Ltan(x1);
    float y2 = Ltan(x1+1);
    return y1 + (y2-y1)*(angle*1000/PI-x1);
}

uchar LUT::degreeToBrad(float angle)
{
    angle = NumberUtility::wrapValue(angle,359.0f);
    #ifdef PENJIN_FIXED
        return fixedpoint::fix2int(angle*32*POINT_ZERO_TWO_TWO);
    #else
        return angle*32*POINT_ZERO_TWO_TWO;
    #endif
}

uchar LUT::radianToBrad(CRfloat angle)
{
    return (degreeToBrad(angle*FIXED_PI*POINT_ZERO_ZERO_FIVE_FIVE));
}

float LUT::bradToDegree(CRuchar angle)
{
    return angle*45*POINT_ZERO_THREE_ONE;
}

float LUT::bradToRadian(CRuchar angle)
{
    return bradToDegree(angle)*180*ONE_OVER_PI;
}

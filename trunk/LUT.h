#ifndef LUT_H_INCLUDED
#define LUT_H_INCLUDED

/*
Pirate Games
Lookup tables for Trig functions intended for use on limited systems.
Uses 256 devisions per circle rather than 360
Written by Kevin Winfield-Pantoja
*/
#include "PenjinTypes.h"
#include "NumberUtility.h"
#include <cmath>

#ifndef PI
    #define PI 3.141592654f
#endif

namespace LUT
{
    /// Setup - MUST be init before use!
    void init();
    void deInit();
    /// Trig functions
    float Lsin(uchar angle);
    float Lcos(CRuchar angle);
    float Ltan(uchar angle);
    // Trig functions with interpolation between values
    // Caution, will not be accurate.
    float LIsin(float angle);
    float LIcos(float angle);
    float LItan(float angle);

    /// Conversion
    uchar degreeToBrad(float angle);
    uchar radianToBrad(CRfloat angle);
    float bradToDegree(CRuchar angle);
    float bradToRadian(CRuchar angle);

    //  These are all to avoid divisions.
    const float POINT_ZERO_ZERO_FIVE_FIVE = 0.005555556f;
    const float POINT_ZERO_TWO_TWO = 0.02222222f;
    const float POINT_ZERO_THREE_ONE = 0.03125f;
    const float ONE_OVER_TWOFIVESIX = 0.00390625f;
    const float ONE_OVER_PI = 0.318309886f;
}
#endif // LUT_H_INCLUDED

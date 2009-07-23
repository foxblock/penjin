#include "PenjinFixedFunc.h"
using namespace fixedpoint;
fixed_point<16> fixedpoint::fixsqrt16(fixed_point<16> a)
{
    fixed_point<16> b;
    b.intValue = fixsqrt16(a.intValue);
    return b;
}


#ifndef PENJINFIXEDFUNC_H_INCLUDED
#define PENJINFIXEDFUNC_H_INCLUDED
#include "trenki/fixed_class.h"
#include "trenki/fixed_func.h"
#include "trenki/vector_math.h"
namespace fixedpoint
{
    template <int p>
    int fix2int(int32_t f){return (f << p);}

    template <int p>
    int fix2int(fixed_point<p> f){return (f.intValue << p);}

    template <int p>
    vmath::vec2<int> fix2int(vmath::vec2<fixedpoint::fixed_point<p> > f){return vmath::vec2<int>(fix2int(f.x),fix2int(f.y));}

    template <int p>
    vmath::vec3<int> fix2int(vmath::vec3<fixedpoint::fixed_point<p> > f){return vmath::vec3<int>(fix2int(f.x),fix2int(f.y),fix2int(f.z));}

    template <int p>
    vmath::vec2<float> fix2float(vmath::vec2<fixedpoint::fixed_point<p> > f){return vmath::vec2<float>(fix2float(f.x),fix2float(f.y));}

    template <int p>
    vmath::vec3<float> fix2float(vmath::vec3<fixedpoint::fixed_point<p> > f){return vmath::vec3<float>(fix2float(f.x),fix2float(f.y),fix2float(f.z));}

    template <int p>
    float fix2float(fixed_point<p> f){return (float)f.intValue / (1 << p);}

    fixed_point<16> fixsqrt16(fixed_point<16> a);
}
#endif // PENJINFIXEDFUNC_H_INCLUDED

#ifndef TYPES_H
#define TYPES_H/*
NOTE: Be very careful with inclusion as the typedefs will affect any headers included afterwards!
*/

#include <string>
//#include "PenjinFixedFunc.h"    // Fixed point
#include "vector_math.h"        //  Vectors
#include "Vector2df.h"
#include "Vector2dx.h"
#include "Vector2di.h"
#include "Vector3df.h"
#include "Vector3dx.h"
#include "Vector3di.h"

typedef unsigned int uint;
typedef unsigned short ushort;
typedef unsigned char uchar;

typedef fixedpoint::fixed_point<16> Fixed;                      //  Default fixed point
typedef vmath::vec4<int> Vector4di;                             //  int 4d vector
typedef vmath::vec4<float> Vector4df;                           //  float 4d vector
typedef vmath::vec4<fixedpoint::fixed_point<16> > Vector4dx;    //  Fixed point 4d vector

// CONSTANT REFERENCES
typedef const bool& CRbool;
typedef const int& CRint;
typedef const unsigned int& CRuint;
typedef const short& CRshort;
typedef const unsigned short& CRushort;
typedef const char& CRchar;
typedef const unsigned char& CRuchar;
typedef const long& CRlong;
typedef const unsigned long& CRulong;
typedef const float& CRfloat;
typedef const double& CRdouble;
typedef const Fixed& CRFixed;
typedef const std::string& CRstring;

//  #undef as necessary
#ifdef PENJIN_FIXED
    /// Forced float types
    typedef float FLOAT;
    typedef const float& CRFLOAT;
    typedef Vector2df VECTOR2DF;
    typedef Vector3df VECTOR3DF;
    typedef Vector4df VECTOR4DF;
    /// float to Fixed conversion
    #define Vector2df Vector2dx
    #define Vector3df Vector3dx
    #define Vector4df Vector4dx
    #define float Fixed
    #define CRfloat CRFixed
#endif  //  PENJIN_FIXED

#include "userTypes.h"
#include "Variable.h"	        // multiple type storage
#endif	//	TYPES_H

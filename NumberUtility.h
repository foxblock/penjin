/*
	Penjin is Copyright (c)2005, 2006, 2007, 2008, 2009, 2010 Kevin Winfield-Pantoja

	This file is part of Penjin.

	Penjin is free software: you can redistribute it and/or modify
	it under the terms of the GNU Lesser General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	Penjin is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU Lesser General Public License for more details.

	You should have received a copy of the GNU Lesser General Public License
	along with Penjin.  If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef NUMBERUTILITY_H_INCLUDED
#define NUMBERUTILITY_H_INCLUDED

#include "PenjinTypes.h"

#ifndef M_PI
    #define M_PI 3.141592653f
#endif
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
    template <class T>
    T signMax(const T& a, const T&b); // Max function, checking for absolute max, but returns value regarding sign of a
    template <class T>
    T signMin(const T& a, const T&b);
    template <class T>
    T closestToZero(const T& a, const T& b);
    template <class T>
    T furthestFromZero(const T& a, const T& b);

    //int wrapValue(int value, CRint limit);
    template <class T>
    T wrapValue(T val,const T& limit)
    {
    //    	We need to keep going until it is within the required range.
        while(val < 0 || val >limit)
        {
    //        	We can't have it less than 0, as it causes problems.
            if(val < 0)
            {
    //             compensate upwards
                val += limit;
            }
    //        	We can't have it more than the limit either
            else if(val > limit)
            {
    //            	compensate downwards
                val -= limit;
            }
        }
        return val;
    }

    /// Angles
    float degToRad(CRfloat a);
    float radToDeg(CRfloat a);
};

#include "NumberUtility.inl"

#endif // NUMBERUTILITY_H_INCLUDED

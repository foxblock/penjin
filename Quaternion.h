#ifndef INC_QUATERNION_H
#define INC_QUATERNION_H

#ifndef _USE_MATH_DEFINES
#define _USE_MATH_DEFINES
#endif

#include "Vector3d.h"
#include <SDL/SDL_opengl.h>
#include <cmath>

class Quaternion
{
	public :

		float s;		//Scalar component
		Vector3d v;		//Vector component

	/* Constructors */
        Quaternion();
        Quaternion(const float& w,const float& x,const float& y,const float& z);
        Quaternion(const float& roll,const float& pitch,const float& yaw);

	/* Operators */
        Quaternion operator=(const Quaternion& q);
        Quaternion operator*(const Quaternion& q);
        Quaternion operator~();

	/* Functions to Create Quaternions */
        Quaternion createFromEuler(float roll, float pitch, float yaw);

	/* Functions to Convert Quaternions */
        Vector3d convertToEuler();
        void convertToMatrix(GLfloat m[16]);

        Quaternion Slerp(const Quaternion& current,const Quaternion& target,const float& t);
};
#endif

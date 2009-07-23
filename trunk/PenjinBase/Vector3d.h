#ifndef INC_VECTOR3D_H
#define INC_VECTOR3D_H

#include <cmath>
#ifdef PENJIN3D
#include <SDL/SDL_opengl.h>
#endif
#include "PenjinTypes.h"

class Vector3d
{
	public:
		float x, y, z;

	Vector3d()
	{
		this->x = 0.0f;
		this->y = 0.0f;
		this->z = 0.0f;
	}

	Vector3d(const float& x,const float& y,const float& z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}
    Vector3d(const Vector3df& vec)
    {
        this->x = vec.x;
		this->y = vec.y;
		this->z = vec.z;
    }
	bool operator== ( Vector3d& v );
	Vector3d operator- ();
	const Vector3d& operator= ( const Vector3d& v );
	const Vector3d& operator= ( const Vector3df& v );
	const Vector3d& operator+= ( const Vector3d& v );
	const Vector3d& operator-= ( const Vector3d& v );
	const Vector3d& operator*= ( const float& s );
	const Vector3d& operator/= ( const float& s );
	const Vector3d operator+ ( const Vector3d& v ) const;
	const Vector3d operator- ( const Vector3d& v ) const;
	const Vector3d operator* ( const float& s ) const;
	const Vector3d operator/ (double s) const;
	const float dot( const Vector3d& v ) const;
	const float length() const;
	const float lengthSquared() const;
	const Vector3d unit() const;
	void normalise();

	friend inline const Vector3d operator* ( const float& s, const Vector3d& v )
	{
		return v*s;
	}

	Vector3d normcrossprod(Vector3d v);
	Vector3d crossprod(Vector3d v);

	const Vector3d operator* ( float m[16] );
	const Vector3d& operator*= ( float m[16] );

	float* getVector();
	Vector3df getVector3df(){return Vector3df(x,y,z);}
};

#endif

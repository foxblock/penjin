#include "Quaternion.h"

Quaternion::Quaternion()
{
	s = v.x = v.y = v.z = 0.0;
}

Quaternion::Quaternion(const float& w,const float& x,const float& y,const float& z)
{
	s = w;
	v.x = x;
	v.y = y;
	v.z = z;
}

Quaternion::Quaternion(const float& roll,const float& pitch,const float& yaw)
{
	*this = createFromEuler(roll, pitch, yaw);
}

Quaternion Quaternion::operator=(const Quaternion& q)
{
	this->s = q.s;
	this->v = q.v;

	return *this;
}

Quaternion Quaternion::operator*(const Quaternion& q)
{
	Quaternion temp;

	temp.s = this->s*q.s - this->v.x*q.v.x - this->v.y*q.v.y - this->v.z*q.v.z;
	temp.v.x = this->s*q.v.x + this->v.x*q.s + this->v.y*q.v.z - this->v.z*q.v.y;
	temp.v.y = this->s*q.v.y + this->v.y*q.s + this->v.z*q.v.x - this->v.x*q.v.z;
	temp.v.z = this->s*q.v.z + this->v.z*q.s + this->v.x*q.v.y - this->v.y*q.v.x;

	return temp;
}

Quaternion Quaternion::operator~()
{
	Quaternion temp;

	temp.s = this->s;
	temp.v.x = -this->v.x;
	temp.v.y = -this->v.y;
	temp.v.z = -this->v.z;

	return temp;
}

Quaternion Quaternion::createFromEuler(float roll,float pitch,float yaw)
{
	Quaternion	temp;

	roll = roll * M_PI / 180.0f;
	pitch = pitch * M_PI / 180.0f;
	yaw = yaw * M_PI / 180.0f;

	float	cyaw, cpitch, croll, syaw, spitch, sroll;
	float	cyawcpitch, syawspitch, cyawspitch, syawcpitch;

	cyaw = cos(0.5f * yaw);
	cpitch = cos(0.5f * pitch);
	croll = cos(0.5f * roll);
	syaw = sin(0.5f * yaw);
	spitch = sin(0.5f * pitch);
	sroll = sin(0.5f * roll);

	cyawcpitch = cyaw*cpitch;
	syawspitch = syaw*spitch;
	cyawspitch = cyaw*spitch;
	syawcpitch = syaw*cpitch;

	temp.s = (float) (cyawcpitch * croll + syawspitch * sroll);
	temp.v.x = (float) (cyawcpitch * sroll - syawspitch * croll);
	temp.v.y = (float) (cyawspitch * croll + syawcpitch * sroll);
	temp.v.z = (float) (syawcpitch * croll - cyawspitch * sroll);

	return temp;
}

Vector3d Quaternion::convertToEuler()
{
	Vector3d temp;

	double	r11, r21, r31, r32, r33, r12, r13;
	double	q00, q11, q22, q33;
	double	tmp;

	q00 = this->s * this->s;
	q11 = this->v.x * this->v.x;
	q22 = this->v.y * this->v.y;
	q33 = this->v.z * this->v.z;

	r11 = q00 + q11 - q22 - q33;
	r21 = 2 * (this->v.x*this->v.y + this->s*this->v.z);
	r31 = 2 * (this->v.x*this->v.z - this->s*this->v.y);
	r32 = 2 * (this->v.y*this->v.z + this->s*this->v.x);
	r33 = q00 - q11 - q22 + q33;

	tmp = fabs(r31);
	if(tmp > 0.999999f)
	{
		r12 = 2 * (this->v.x*this->v.y - this->s*this->v.z);
		r13 = 2 * (this->v.x*this->v.z + this->s*this->v.y);

		temp.x = 0.0;
		temp.y = ((double) (-(M_PI/2) * r31/tmp))* 180.0f / M_PI;
		temp.z = ((double) atan2(-r12, -r31*r13))* 180.0f / M_PI;
		return temp;
	}

	temp.x = ((float) atan2(r32, r33))* 180.0f / M_PI;
	temp.y = ((float) asin(-r31))* 180.0f / M_PI;
	temp.z = ((float) atan2(r21, r11))* 180.0f / M_PI;

	return temp;
}

void Quaternion::convertToMatrix(GLfloat m[16])
{
    float wx, wy, wz, xx, yy, yz, xy, xz, zz, x2, y2, z2;

    // calculate coefficients
    x2 = this->v.x + this->v.x; y2 = this->v.y + this->v.y;
    z2 = this->v.z + this->v.z;
    xx = this->v.x * x2; xy = this->v.x * y2; xz = this->v.x * z2;
    yy = this->v.y * y2; yz = this->v.y * z2; zz = this->v.z * z2;
    wx = this->s * x2; wy = this->s * y2; wz = this->s * z2;

    m[0] = 1.0f - (yy + zz);
	m[4] = xy - wz;
    m[8] = xz + wy;
	m[12] = 0.0f;

    m[1] = xy + wz;
	m[5] = 1.0f - (xx + zz);
    m[9] = yz - wx;
	m[13] = 0.0f;

    m[2] = xz - wy;
	m[6] = yz + wx;
    m[10] = 1.0f - (xx + yy);
	m[14] = 0.0f;

    m[3] = 0.0f;
	m[7] = 0.0f;
    m[11] = 0.0f;
	m[15] = 1.0f;
}

Quaternion Quaternion::Slerp(const Quaternion& current,const Quaternion& target,const float& t)
{
	float to[4];
	double omega, cosom, sinom, scale0, scale1;
	Quaternion temp;

	cosom = current.v.x * target.v.x + current.v.y * target.v.y + current.v.z * target.v.z + current.s * target.s;

	if( cosom < 0.0 )
	{
		cosom = -cosom;
		to[0] = -target.v.x;
		to[1] = -target.v.y;
		to[2] = -target.v.z;
		to[3] = -target.s;
	}
	else
	{
		to[0] = target.v.x;
		to[1] = target.v.y;
		to[2] = target.v.z;
		to[3] = target.s;
	}

    if( (1.0 - cosom) > 0.00001 )
	{
		omega = acos(cosom);
		sinom = sin(omega);
		scale0 = sin((1.0 - t) * omega) / sinom;
		scale1 = sin(t * omega) / sinom;
	}
	else
	{
		scale0 = 1.0 - t;
		scale1 = t;
	}

	temp.v.x = scale0 * current.v.x + scale1 * to[0];
	temp.v.y = scale0 * current.v.y + scale1 * to[1];
	temp.v.z = scale0 * current.v.z + scale1 * to[2];
	temp.s = scale0 * current.s + scale1 * to[3];

	return temp;
}

//---------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//---------------------------------------------------------------

#include "Vect4D.h"

Vect4D::Vect4D()
	:	x(0), y(0), z(0), w(1)
{
}

Vect4D::Vect4D(float tx, float ty, float tz, float tw)
	: x(tx), y(ty), z(tz), w(tw)
{
}

Vect4D::Vect4D(__m128 m)
	: _m(m)
{
}

Vect4D::~Vect4D()
{
	// nothing to delete
}

void Vect4D::norm(Vect4D &v)
{
	float mag = sqrt(this->x * this->x + this->y * this->y + this->z * this->z);

	if(0 < mag)
	{
		v.x = this->x / mag;
		v.y = this->y / mag;
		v.z = this->z / mag;
		v.w = 1;
	}
}

Vect4D Vect4D::operator + (Vect4D t)
{
	Vect4D ans;

	ans.x = this->x + t.x;
	ans.y = this->y + t.y;
	ans.z = this->z + t.z;

	return ans;
}

float &Vect4D::operator[](Vect e)
{
	switch(e)
	{
	case Vect::X:
		return x;
		break;
	case Vect::Y:
		return y;
		break;
	case Vect::Z:
		return z;
		break;
	case Vect::W:
		return w;
		break;
	default:
		assert(0);
		return x;
	}
}

Vect4D Vect4D::operator *(float scale)
{
	Vect4D tmp;
	tmp.x = this->x * scale;
	tmp.y = this->y * scale;
	tmp.z = this->z * scale;

	return tmp;
}

Vect4D Vect4D::operator - (Vect4D t)
{
	Vect4D out;

	out.x = this->x - t.x;
	out.y = this->y - t.y;
	out.z = this->z - t.z;
	
	return out;
	//return Vect4D(this->x - t.x, this->y - t.y, this->z - t.z);
}

void Vect4D::Cross(Vect4D &vin, Vect4D &vout)
{
	/*
	Vect4D a;
	Vect4D b;
	Vect4D c;

	a = _mm_shuffle_ps(this->_m, this->_m, _MM_SHUFFLE(3, 0, 2, 1));
	b = _mm_shuffle_ps(vin._m, vin._m, _MM_SHUFFLE(3, 1, 0, 2));
	a = _mm_mul_ps(a._m, b._m);
	c = _mm_shuffle_ps(vin._m, vin._m, _MM_SHUFFLE(3, 0, 2, 1));
	b = _mm_shuffle_ps(this->_m, this->_m, _MM_SHUFFLE(3, 1, 0, 2));
	c = _mm_mul_ps(c._m, b._m);
	b = _mm_sub_ps(a._m, c._m);
	b.w = 1;
	vout = b;
	*/

	vout.x = (y * vin.z - z * vin.y);
	vout.y = (z * vin.x - x * vin.z);
	vout.z = (x * vin.y - y * vin.x);
	vout.w = 1;
}

void Vect4D::set(float tx, float ty, float tz, float tw)
{
	this->x = tx;
	this->y = ty;
	this->z = tz;
	this->w = tw;
}

// --- End of File ---

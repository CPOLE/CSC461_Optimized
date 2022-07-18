//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "Vect_vM_SIMD.h"
#include "Matrix_vM_SIMD.h"

Vect_vM_SIMD::Vect_vM_SIMD(const float tx, const float ty, const float tz, const float tw)
	: x(tx), y(ty), z(tz), w(tw)
{
}

Vect_vM_SIMD::Vect_vM_SIMD(__m128 m)
	: _m(m)
{
}

//------------------------------
// For No proxy:
//------------------------------

Vect_vM_SIMD Vect_vM_SIMD::operator * (const Matrix_vM_SIMD &ma) const
{
	return Vect_vM_SIMD(
		_mm_add_ps(
			_mm_mul_ps(_mm_set1_ps(this->x), ma.v0._m),
			_mm_add_ps(
				_mm_mul_ps(_mm_set1_ps(this->y), ma.v1._m),
				_mm_add_ps(
					_mm_mul_ps(_mm_set1_ps(this->z), ma.v2._m),
						_mm_mul_ps(_mm_set1_ps(this->w), ma.v3._m)
					)
				)
			)
		);
};


// ---  End of File ---------------



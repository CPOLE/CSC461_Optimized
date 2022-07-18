//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "Vect_Row_SIMD.h"
#include "Matrix_Row_SIMD.h"

Vect_Row_SIMD::Vect_Row_SIMD(const float tx, const float ty, const float tz, const float tw)
	: x(tx), y(ty), z(tz), w(tw)
{
}

Vect_Row_SIMD::Vect_Row_SIMD(__m128 m)
	: _m(m)
{
}

Vect_Row_SIMD Vect_Row_SIMD::operator * (const Matrix_Row_SIMD& m)
{
	return Vect_Row_SIMD(
		_mm_add_ps(
			_mm_mul_ps(_mm_set1_ps(this->x), m.v0._m),
			_mm_add_ps(
				_mm_mul_ps(_mm_set1_ps(this->y), m.v1._m),
				_mm_add_ps(
					_mm_mul_ps(_mm_set1_ps(this->z), m.v2._m),
					_mm_mul_ps(_mm_set1_ps(this->w), m.v3._m)
				)
			)
		)
	);
}


// ---  End of File ---------------
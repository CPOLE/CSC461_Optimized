//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "Vect_M_SIMD.h"
#include "Matrix_M_SIMD.h"

Matrix_M_SIMD::Matrix_M_SIMD(const Vect_M_SIMD& tV0,
	const Vect_M_SIMD& tV1,
	const Vect_M_SIMD& tV2,
	const Vect_M_SIMD& tV3)
	: v0(tV0), v1(tV1), v2(tV2), v3(tV3)
{
}

Matrix_M_SIMD Matrix_M_SIMD::operator * (const Matrix_M_SIMD& mb) const
{
	Matrix_M_SIMD A;
	
	//	1
	__m128 tmp1 = _mm_mul_ps(_mm_set1_ps(this->m0), mb.v0._m);
	__m128 tmp2 = _mm_mul_ps(_mm_set1_ps(this->m1), mb.v1._m);
	__m128 tmp3 = _mm_mul_ps(_mm_set1_ps(this->m2), mb.v2._m);
	__m128 tmp4 = _mm_mul_ps(_mm_set1_ps(this->m3), mb.v3._m);
	A.v0 = _mm_add_ps(tmp1,
				_mm_add_ps(tmp2,
					_mm_add_ps(tmp3,tmp4)
				)
			);

	//	2
	tmp1 = _mm_mul_ps(_mm_set1_ps(this->m4), mb.v0._m);
	tmp2 = _mm_mul_ps(_mm_set1_ps(this->m5), mb.v1._m);
	tmp3 = _mm_mul_ps(_mm_set1_ps(this->m6), mb.v2._m);
	tmp4 = _mm_mul_ps(_mm_set1_ps(this->m7), mb.v3._m);
	A.v1 = _mm_add_ps(tmp1,
			_mm_add_ps(tmp2,
				_mm_add_ps(tmp3, tmp4)
			)
		);

	//	3
	tmp1 = _mm_mul_ps(_mm_set1_ps(this->m8), mb.v0._m);
	tmp2 = _mm_mul_ps(_mm_set1_ps(this->m9), mb.v1._m);
	tmp3 = _mm_mul_ps(_mm_set1_ps(this->m10), mb.v2._m);
	tmp4 = _mm_mul_ps(_mm_set1_ps(this->m11), mb.v3._m);
	A.v2 = _mm_add_ps(tmp1,
			_mm_add_ps(tmp2,
				_mm_add_ps(tmp3, tmp4)
			)
		);

	//	4
	tmp1 = _mm_mul_ps(_mm_set1_ps(this->m12), mb.v0._m);
	tmp2 = _mm_mul_ps(_mm_set1_ps(this->m13), mb.v1._m);
	tmp3 = _mm_mul_ps(_mm_set1_ps(this->m14), mb.v2._m);
	tmp4 = _mm_mul_ps(_mm_set1_ps(this->m15), mb.v3._m);
	A.v3 = _mm_add_ps(tmp1,
			_mm_add_ps(tmp2,
				_mm_add_ps(tmp3, tmp4)
			)
		);

	return A;
}


// ---  End of File ---------------

//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "Vect_Col_SIMD.h"
#include "Matrix_Col_SIMD.h"

Matrix_Col_SIMD::Matrix_Col_SIMD(const Vect_Col_SIMD &tV0,
								 const Vect_Col_SIMD &tV1,
								 const Vect_Col_SIMD &tV2,
								 const Vect_Col_SIMD &tV3)
	: v0(tV0), v1(tV1), v2(tV2), v3(tV3)
{
}

//	(5) m * v
M5v::operator Vect_Col_SIMD() {
	Vect_Col_SIMD A;

	A = _mm_hadd_ps(
		_mm_hadd_ps(
			_mm_mul_ps(m5.v0._m, v._m),
			_mm_mul_ps(m5.v1._m, v._m)
		),
		_mm_hadd_ps(
			_mm_mul_ps(m5.v2._m, v._m),
			_mm_mul_ps(m5.v3._m, v._m)
		)
	);

	A = _mm_hadd_ps(
		_mm_hadd_ps(
			_mm_mul_ps(m4.v0._m, A._m),
			_mm_mul_ps(m4.v1._m, A._m)
		),
		_mm_hadd_ps(
			_mm_mul_ps(m4.v2._m, A._m),
			_mm_mul_ps(m4.v3._m, A._m)
		)
	);

	A = _mm_hadd_ps(
		_mm_hadd_ps(
			_mm_mul_ps(m3.v0._m, A._m),
			_mm_mul_ps(m3.v1._m, A._m)
		),
		_mm_hadd_ps(
			_mm_mul_ps(m3.v2._m, A._m),
			_mm_mul_ps(m3.v3._m, A._m)
		)
		);

	A = _mm_hadd_ps(
		_mm_hadd_ps(
			_mm_mul_ps(m2.v0._m, A._m),
			_mm_mul_ps(m2.v1._m, A._m)
		),
		_mm_hadd_ps(
			_mm_mul_ps(m2.v2._m, A._m),
			_mm_mul_ps(m2.v3._m, A._m)
		)
	);

	A = _mm_hadd_ps(
		_mm_hadd_ps(
			_mm_mul_ps(m1.v0._m, A._m),
			_mm_mul_ps(m1.v1._m, A._m)
		),
		_mm_hadd_ps(
			_mm_mul_ps(m1.v2._m, A._m),
			_mm_mul_ps(m1.v3._m, A._m)
		)
	);
	return A;
}


// ---  End of File ---------------

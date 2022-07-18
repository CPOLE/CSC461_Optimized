//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "Vect_Mv_SIMD.h"
#include "Matrix_Mv_SIMD.h"

Vect_Mv_SIMD::Vect_Mv_SIMD(const float tx, const float ty, const float tz, const float tw)
	: x(tx), y(ty), z(tz), w(tw)
{
}

Vect_Mv_SIMD::Vect_Mv_SIMD(__m128 m)
	: _m(m)
{
}

// ---  End of File ---------------



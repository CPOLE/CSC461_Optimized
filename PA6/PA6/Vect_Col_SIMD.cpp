//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "Vect_Col_SIMD.h"


Vect_Col_SIMD::Vect_Col_SIMD(const float tx, const float ty, const float tz, const float tw)
	: x(tx), y(ty), z(tz), w(tw)
{
}

Vect_Col_SIMD::Vect_Col_SIMD(__m128 m)
	: _m(m)
{
}

// ---  End of File ---------------



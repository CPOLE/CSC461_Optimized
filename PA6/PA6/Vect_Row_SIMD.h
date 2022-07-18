//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef Vect_Row_SIMD_H
#define Vect_Row_SIMD_H

#include <xmmintrin.h>
#include <smmintrin.h>  

class Matrix_Row_SIMD;

// -----------------------------------------------------------------------
// Rules: 
//    Implement for Row Major
//    No implementation in Header
//
//    Proxy (optional)
//    
//        Proxies are the only thing that can have the keyword "inline"
//            inline only for subsitution resolving.. that's it
//                No constructors or other operators... only proxy for substituion purpose
//            example:  (this is allowed)
//                inline vM operator * (const Vect_Row_SIMD &v, const Matrix_Row_SIMD &m)
//        No proxy implementation in header
//            conversion operator needs to be implemented in CPP file
//            proxy constructors are allowed in header (only exception)
// -----------------------------------------------------------------------

class Vect_Row_SIMD
{
public:
	Vect_Row_SIMD() = default;
	Vect_Row_SIMD(const Vect_Row_SIMD &tmp) = default;
	Vect_Row_SIMD &operator = (const Vect_Row_SIMD &tmp) = default;
	~Vect_Row_SIMD() = default;
	Vect_Row_SIMD(__m128 m);

	Vect_Row_SIMD operator * (const Matrix_Row_SIMD& m);

	Vect_Row_SIMD(const float tx, const float ty, const float tz, const float tw);

public:

	// anonymous union
	union
	{
		__m128	_m;

		// anonymous struct
		struct
		{
			float x;
			float y;
			float z;
			float w;
		};
	};

private:
	friend struct v1M;
	friend struct v2M;
	friend struct v3M;
	friend struct v4M;
	friend struct v5M;
};

//	v * m
struct v1M {
	const Vect_Row_SIMD& v;
	const Matrix_Row_SIMD& m1;
	v1M(const Vect_Row_SIMD& _v, const Matrix_Row_SIMD& _m)
		: v(_v), m1(_m) {
	};
};

//	v * (2) m
struct v2M {
	const Vect_Row_SIMD& v;
	const Matrix_Row_SIMD& m2;
	v2M(const Vect_Row_SIMD& _v, const Matrix_Row_SIMD& _m)
		: v(_v), m2(_m) {
	};
};

//	v * (3) m
struct v3M {
	const Vect_Row_SIMD& v;
	const Matrix_Row_SIMD& m3;
	v3M(const Vect_Row_SIMD& _v, const Matrix_Row_SIMD& _m)
		: v(_v), m3(_m) {
	};
};

//	v * (4) m
struct v4M {
	const Vect_Row_SIMD& v;
	const Matrix_Row_SIMD& m4;
	v4M(const Vect_Row_SIMD& _v, const Matrix_Row_SIMD& _m)
		: v(_v), m4(_m) {
	};
};

//	v * (5) m
struct v5M {
	const Vect_Row_SIMD& v;
	const Matrix_Row_SIMD& m5;
	v5M(const Vect_Row_SIMD& _v, const Matrix_Row_SIMD& _m)
		: v(_v), m5(_m) {
	};
};


#endif

// ---  End of File ---------------

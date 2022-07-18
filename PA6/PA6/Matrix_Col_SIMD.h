//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef Matrix_Col_SIMD_H
#define Matrix_Col_SIMD_H

#include "Vect_Col_SIMD.h"
   
// -----------------------------------------------------------------------
// Rules: 
//    Implement for Col Major
//    No implementation in Header
//
//    Proxy (optional)
//    
//        Proxies are the only thing that can have the keyword "inline"
//            inline only for subsitution resolving.. that's it
//                No constructors or other operators... only proxy for substituion purpose
//            example:  (this is allowed)
//                inline MM operator * (const Matrix_Col_SIMD &m, const Matrix_Col_SIMD &n)
//        No proxy implementation in header
//            conversion operator needs to be implemented in CPP file
//            proxy constructors are allowed in header (only exception)
// -----------------------------------------------------------------------

class Matrix_Col_SIMD
{
public:
	Matrix_Col_SIMD() = default;
	Matrix_Col_SIMD(const Matrix_Col_SIMD &tmp) = default;
	Matrix_Col_SIMD &operator=(const Matrix_Col_SIMD &tmp) = default;
	~Matrix_Col_SIMD() = default;

	Matrix_Col_SIMD(const Vect_Col_SIMD &tV0,
					const Vect_Col_SIMD &tV1,
					const Vect_Col_SIMD &tV2,
					const Vect_Col_SIMD &tV3);

	union
	{
		struct
		{
			Vect_Col_SIMD v0;
			Vect_Col_SIMD v1;
			Vect_Col_SIMD v2;
			Vect_Col_SIMD v3;
		};

		struct
		{
			float m0;
			float m1;
			float m2;
			float m3;
			float m4;
			float m5;
			float m6;
			float m7;
			float m8;
			float m9;
			float m10;
			float m11;
			float m12;
			float m13;
			float m14;
			float m15;
		};
	};

	friend struct m1M;
	friend struct m2M;
	friend struct m3M;
	friend struct m4M;
	friend struct M5v;
};

//	m * m
struct m1M {
	const Matrix_Col_SIMD& m1;
	const Matrix_Col_SIMD& m2;

	m1M(const Matrix_Col_SIMD& _m1, const Matrix_Col_SIMD& _m2)
		: m1(_m1), m2(_m2) {
	};
};
inline m1M operator * (const Matrix_Col_SIMD& _m1, const Matrix_Col_SIMD& _m2) {
	return m1M(_m1, _m2);
}

//	m * (2) m
struct m2M {
	const Matrix_Col_SIMD& m1;
	const Matrix_Col_SIMD& m2;
	const Matrix_Col_SIMD& m3;

	m2M(const m1M& _m1M, const Matrix_Col_SIMD& _m)
		: m1(_m1M.m1), m2(_m1M.m2), m3(_m) {
	};
};
inline m2M operator * (const m1M& _m1M, const Matrix_Col_SIMD& _m) {
	return m2M(_m1M, _m);
}

//	m * (3) m
struct m3M {
	const Matrix_Col_SIMD& m1;
	const Matrix_Col_SIMD& m2;
	const Matrix_Col_SIMD& m3;
	const Matrix_Col_SIMD& m4;

	m3M(const m2M& _m2M, const Matrix_Col_SIMD& _m)
		: m1(_m2M.m1), m2(_m2M.m2), m3(_m2M.m3), m4(_m) {
	};
};
inline m3M operator * (const m2M& _m2M, const Matrix_Col_SIMD& _m) {
	return m3M(_m2M, _m);
}

//	m * (4) m
struct m4M {
	const Matrix_Col_SIMD& m1;
	const Matrix_Col_SIMD& m2;
	const Matrix_Col_SIMD& m3;
	const Matrix_Col_SIMD& m4;
	const Matrix_Col_SIMD& m5;

	m4M(const m3M& _m3M, const Matrix_Col_SIMD& _m2)
		: m1(_m3M.m1), m2(_m3M.m2), m3(_m3M.m3), m4(_m3M.m4), m5(_m2) {
	};
};
inline m4M operator * (const m3M& _m3M, const Matrix_Col_SIMD& _m) {
	return m4M(_m3M, _m);
}

//	--------------------------------
//	(5) m * v
struct M5v {
	const Matrix_Col_SIMD& m1;
	const Matrix_Col_SIMD& m2;
	const Matrix_Col_SIMD& m3;
	const Matrix_Col_SIMD& m4;
	const Matrix_Col_SIMD& m5;
	const Vect_Col_SIMD& v;

	M5v(const m4M& _m4M, const Vect_Col_SIMD& _v)
		: m1(_m4M.m1), m2(_m4M.m2), m3(_m4M.m3), m4(_m4M.m4), m5(_m4M.m5), v(_v) {
	};
	operator Vect_Col_SIMD();
};
inline M5v operator * (const m4M& _m4M, const Vect_Col_SIMD& _v) {
	return M5v(_m4M, _v);
}

#endif

// ---  End of File ---------------

//---------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//---------------------------------------------------------------

#include <Math.h>
#include "Vect4d.h"
#include "Matrix.h"

Matrix::Matrix()
	: m0(0), m1(0), m2(0), m3(0), m4(0), m5(0), m6(0), m7(0), m8(0), m9(0), m10(0), m11(0), m12(0), m13(0), m14(0), m15(0)
{	
}

Matrix::Matrix(Matrix& t)
	: m0(t.m0), m1(t.m1), m2(t.m2), m3(t.m3), m4(t.m4), m5(t.m5), m6(t.m6), m7(t.m7), m8(t.m8), m9(t.m9), m10(t.m10), m11(t.m11), m12(t.m12), m13(t.m13), m14(t.m14), m15(t.m15)
{
}

Matrix::~Matrix()
{
}

void Matrix::setIdentMatrix()
{ 
	//this->v0.set(1, 0, 0, 0);
	this->m0 = 1;
	//this->m1 = 0;
	//this->m2 = 0;
	//this->m3 = 0;

	//this->v1.set(0, 1, 0, 0);
	//this->m4 = 0;
	this->m5 = 1;
	//this->m6 = 0;
	//this->m7 = 0;

	//this->v2.set(0, 0, 1, 0);
	//this->m8 = 0;
	//this->m9 = 0;
	this->m10 = 1;
	//this->m11 = 0;
	
	//this->v3.set(0, 0, 0, 1);
	//this->m12 = 0;
	//this->m13 = 0;
	//this->m14 = 0;
	this->m15 = 1;
}

void Matrix::setTransMatrix(Vect4D *t)
{ 
	//this->v0.set(1, 0, 0, 0);
	this->m0 = 1;
	//this->m1 = 0;
	//this->m2 = 0;
	//this->m3 = 0;

	//this->v1.set(0, 1, 0, 0);
	//this->m4 = 0;
	this->m5 = 1;
	//this->m6 = 0;
	//this->m7 = 0;

	//this->v2.set(0, 0, 1, 0);
	//this->m8 = 0;
	//this->m9 = 0;
	this->m10 = 1;
	//this->m11 = 0;
	
	this->v3.set(t->x, t->y, t->z, 1);
	//this->m12 = t->x;
	//this->m13 = t->y;
	//this->m14 = t->z;
	//this->m15 = 1;
}

/*
void Matrix::set( MatrixRow row, Vect4D *t )
{
	switch( row )
	{
	case MatrixRow::MATRIX_ROW_0:
		//this->v0.set(t->x, t->y, t->z, t->w);
		this->m0 = t->x;
		this->m1 = t->y;
		this->m2 = t->z;
		this->m3 = t->w;
		break;

	case MatrixRow::MATRIX_ROW_1:
		//this->v1.set(t->x, t->y, t->z, t->w);
		this->m4 = t->x;
		this->m5 = t->y;
		this->m6 = t->z;
		this->m7 = t->w;
		break;

	case MatrixRow::MATRIX_ROW_2:
		//this->v2.set(t->x, t->y, t->z, t->w);
		this->m8 = t->x;
		this->m9 = t->y;
		this->m10 = t->z;
		this->m11 = t->w;
		break;

	case MatrixRow::MATRIX_ROW_3:
		//this->v3.set(t->x, t->y, t->z, t->w);
		this->m12 = t->x;
		this->m13 = t->y;
		this->m14 = t->z;
		this->m15 = t->w;
		break;

	default:
		// should never get here, if we are here something bad has happened
		assert(0);
	}
}
*/

/*
float &Matrix::operator[](Index e)
{
	// get the individual elements
	switch(e)
	{
	case Index::m0:
		return m0;
		break;
	case Index::m1:
		return m1;
		break;
	case Index::m2:
		return m2;
		break;
	case Index::m3:
		return m3;
		break;
	case Index::m4:
		return m4;
		break;
	case Index::m5:
		return m5;
		break;
	case Index::m6:
		return m6;
		break;
	case Index::m7:
		return m7;
		break;
	case Index::m8:
		return m8;
		break;
	case Index::m9:
		return m9;
		break;	
	case Index::m10:
		return m10;
		break;
	case Index::m11:
		return m11;
		break;	
	case Index::m12:
		return m12;
		break;	
	case Index::m13:
		return m13;
		break;	
	case Index::m14:
		return m14;
		break;
	case Index::m15:
		return m15;
		break;
	default:
		assert(0);
		return m0;
		break;
	}
}

void Matrix::get( MatrixRow row, Vect4D *t )
{ // get a row of the matrix
	switch( row )
	{
	case MatrixRow::MATRIX_ROW_0:
		//t->set(this->m0, this->m1, this->m2, this->m3);
		//t->_m = _mm_set_ps(this->m0, this->m1, this->m2, this->m3);
		t->x = this->m0;
		t->y = this->m1;
		t->z = this->m2;
		t->w = this->m3;
		break;

	case MatrixRow::MATRIX_ROW_1:
		//t->set(this->m4, this->m5, this->m6, this->m7);
		//t->_m = _mm_set_ps(this->m4, this->m5, this->m6, this->m7);
		t->x = this->m4;
		t->y = this->m5;
		t->z = this->m6;
		t->w = this->m7;
		break;

	case MatrixRow::MATRIX_ROW_2:
		//t->set(this->m8, this->m9, this->m10, this->m11);
		//t->_m = _mm_set_ps(this->m8, this->m9, this->m10, this->m11);
		t->x = this->m8;
		t->y = this->m9;
		t->z = this->m10;
		t->w = this->m11;
		break;

	case MatrixRow::MATRIX_ROW_3:
		//t->set(this->m12, this->m13, this->m14, this->m15);
		//t->_m = _mm_set_ps(this->m12, this->m13, this->m14, this->m15);
		t->x = this->m12;
		t->y = this->m13;
		t->z = this->m14;
		t->w = this->m15;
		break;

	default:
		assert(0);
	}
}
*/

Matrix Matrix::operator*( Matrix& rhs) 
{ 
	Matrix tmp;
	tmp.v0._m =	_mm_add_ps(_mm_mul_ps(_mm_set1_ps(this->m0), rhs.v0._m),
					_mm_add_ps(_mm_mul_ps(_mm_set1_ps(this->m1), rhs.v1._m),
						_mm_add_ps(_mm_mul_ps(_mm_set1_ps(this->m2), rhs.v2._m), _mm_mul_ps(_mm_set1_ps(this->m3), rhs.v3._m))
					)
				);

	tmp.v1._m =	_mm_add_ps(_mm_mul_ps(_mm_set1_ps(this->m4), rhs.v0._m),
					_mm_add_ps(_mm_mul_ps(_mm_set1_ps(this->m5), rhs.v1._m),
						_mm_add_ps(_mm_mul_ps(_mm_set1_ps(this->m6), rhs.v2._m), _mm_mul_ps(_mm_set1_ps(this->m7), rhs.v3._m))
					)
				);

	tmp.v2._m =	_mm_add_ps(_mm_mul_ps(_mm_set1_ps(this->m8), rhs.v0._m),
					_mm_add_ps(_mm_mul_ps(_mm_set1_ps(this->m9), rhs.v1._m),
						_mm_add_ps(_mm_mul_ps(_mm_set1_ps(this->m10), rhs.v2._m), _mm_mul_ps(_mm_set1_ps(this->m11), rhs.v3._m))
					)
				);

	tmp.v3._m = _mm_add_ps(_mm_mul_ps(_mm_set1_ps(this->m12), rhs.v0._m),
					_mm_add_ps(_mm_mul_ps(_mm_set1_ps(this->m13), rhs.v1._m),
						_mm_add_ps(_mm_mul_ps(_mm_set1_ps(this->m14), rhs.v2._m), _mm_mul_ps(_mm_set1_ps(this->m15), rhs.v3._m))
		)
	);

	/*
	tmp.m0 = (m0*rhs.m0) + (m1*rhs.m4) + (m2*rhs.m8) + (m3*rhs.m12);
	tmp.m1 = (m0*rhs.m1) + (m1*rhs.m5) + (m2*rhs.m9) + (m3*rhs.m13);
	tmp.m2 = (m0*rhs.m2) + (m1*rhs.m6) + (m2*rhs.m10) + (m3*rhs.m14);
	tmp.m3 = (m0*rhs.m3) + (m1*rhs.m7) + (m2*rhs.m11) + (m3*rhs.m15);
	
	tmp.m4 = (m4*rhs.m0) + (m5*rhs.m4) + (m6*rhs.m8) + (m7*rhs.m12);
	tmp.m5 = (m4*rhs.m1) + (m5*rhs.m5) + (m6*rhs.m9) + (m7*rhs.m13);
	tmp.m6 = (m4*rhs.m2) + (m5*rhs.m6) + (m6*rhs.m10) + (m7*rhs.m14);
	tmp.m7 = (m4*rhs.m3) + (m5*rhs.m7) + (m6*rhs.m11) + (m7*rhs.m15);
	
	tmp.m8 = (m8*rhs.m0) + (m9*rhs.m4) + (m10*rhs.m8) + (m11*rhs.m12);
	tmp.m9 = (m8*rhs.m1) + (m9*rhs.m5) + (m10*rhs.m9) + (m11*rhs.m13);
	tmp.m10 = (m8*rhs.m2) + (m9*rhs.m6) + (m10*rhs.m10) + (m11*rhs.m14);
	tmp.m11 = (m8*rhs.m3) + (m9*rhs.m7) + (m10*rhs.m11) + (m11*rhs.m15);
	
	tmp.m12 = (m12*rhs.m0) + (m13*rhs.m4) + (m14*rhs.m8) + (m15*rhs.m12);
	tmp.m13 = (m12*rhs.m1) + (m13*rhs.m5) + (m14*rhs.m9) + (m15*rhs.m13);
	tmp.m14 = (m12*rhs.m2) + (m13*rhs.m6) + (m14*rhs.m10) + (m15*rhs.m14);
	tmp.m15 = (m12*rhs.m3) + (m13*rhs.m7) + (m14 *rhs.m11) + (m15*rhs.m15);
	*/
	return tmp;
}

Matrix& Matrix::operator/=(float rhs)
{ 
	// divide each element by a value
	// using inverse multiply trick, faster that individual divides
	float inv_rhs = 1/rhs;

	this->v0._m = _mm_mul_ps(this->v0._m, _mm_set1_ps(inv_rhs));
	this->v1._m = _mm_mul_ps(this->v1._m, _mm_set1_ps(inv_rhs));
	this->v2._m = _mm_mul_ps(this->v2._m, _mm_set1_ps(inv_rhs));
	this->v3._m = _mm_mul_ps(this->v3._m, _mm_set1_ps(inv_rhs));

	/*
	m0 *= inv_rhs;
	m1 *= inv_rhs;
	m2 *= inv_rhs;
	m3 *= inv_rhs;
	m4 *= inv_rhs;
	m5 *= inv_rhs;
	m6 *= inv_rhs;
	m7 *= inv_rhs;
	m8 *= inv_rhs;
	m9 *= inv_rhs;
	m10 *= inv_rhs;
	m11 *= inv_rhs;
	m12 *= inv_rhs;
	m13 *= inv_rhs;
	m14 *= inv_rhs;
	m15 *= inv_rhs;
	*/
	return *this;
}

float Matrix::Determinant()
{
	float ta = (m10 * m15) - (m11 * m14);
	// tb = (kq - mo)
	float tb = (m9 * m15) - (m11 * m13);
	// tc = (kp - lo)
	float tc = (m9 * m14) - (m10 * m13);
	// td = (jq - mn)
	float td = (m8 * m15) - (m11 * m12);
	// te = (jo - kn)
	float te = (m8 * m13) - (m9 *  m12);
	// tf = (jp - ln)
	float tf = (m8 * m14) - (m10 * m12);
	
	return ((m0 * ((m5 * ta) - (m6 * tb) + (m7 * tc)))
			- (m1 * ((m4 * ta) - (m6 * td) + (m7 * tf)))
			+ (m2 * ((m4 * tb) - (m5 * td) + (m7 * te)))
			- (m3 * ((m4 * tc) - (m5 * tf) + (m6 * te))));
	
}

Matrix Matrix::GetAdjugate() 
{
	Matrix tmp;
	
	// load		ABC		(3)		ABC--
	float t1 = (m10*m15) - (m11*m14);
	float t2 = (m9*m15) - (m11*m13);
	float t3 = (m9*m14) - (m10*m13);
	
	// a = f(ta) - g(tb) + h(tc)
	tmp.m0 = (m5*t1) - (m6*t2) + (m7*t3);
	// b = -( b(ta) - c(tb) + d(tc))
	tmp.m1 = -((m1*t1) - (m2*t2) + (m3*t3));
	
	// load		JK		(5)		ABCJK
	float t4 = (m8*m15) - (m11*m12);
	float t5 = (m8*m14) - (m10*m12);
	// e = - ( e(ta) - g(tj) + h(tk))
	tmp.m4 = -( (m4*t1) - (m6*t4) + (m7*t5));
	// f = a(ta) - c(tj) + d(tk)
	tmp.m5 = (m0*t1) - (m2*t4) + (m3*t5);
	
	// unload	AJ		(3)		-BC-K
	// load		P		(4)		PBC-K
	t1 = (m8*m13) - (m9*m12);
	// n = -( e(tc) - f(tk) + g(tp))
	tmp.m12 = -((m4*t3) - (m5*t5) + (m6*t1));
	// o = a(tc) - b(tk) + c(tp)
	tmp.m13 = (m0*t3) - (m1*t5) + (m2*t1);
	
	// unload	KC		(2)		PB---
	// load		J		(3)		PBJ--
	t3 = (m8*m15) - (m11*m12);
	
	// j = e(tb) - f(tj) + h(tp)
	tmp.m8 = (m4*t2) - (m5*t3) + (m7*t1);
	// k = - ( a(tb) - b(tj) + d(tp))
	tmp.m9 = -((m0*t2) - (m1*t3) + (m3*t1));
	
	// unload	BPJ		(0)		-----
	// load		DLM		(3)		DLM--
	t1 = (m6*m15) - (m7*m14);
	t2 = (m4*m15) - (m7*m12);
	t3 = (m4*m14) - (m6*m12);
	
	// g = - ( a(td) - c(tl) + d(tm))
	tmp.m6 = -((m0*t1) - (m2*t2) + (m3*t3));
	
	// load		FR		(5)		DLMFR
	t4 = (m5*m14) - (m6*m13);
	t5 = (m4*m13) - (m5*m12);
	
	// p = - ( a(tf) - b(tm) + c(tr))
	tmp.m14 = -( (m0*t4) - (m1*t3) + (m3*t5));
	
	// unload	M		(4)		DL-FR
	// load		E		(5)		DLEFR
	t3 = (m5*m15) - (m7*m13);
	
	// l = a(te) - b(tl) + d(tr)
	tmp.m10 = (m0*t3) - (m1*t2) + (m3*t5);
	
	// unload	LR		(3)		D-EF-
	// c = b(td) - c(te) + d(tf)
	tmp.m2 = (m1*t1) - (m2*t3) + (m3*t4);
	
	// unload	DEF		(0)		-----
	// load		GHI		(3)		GHI--
	t1 = (m6*m11) - (m7*m10);
	t2 = (m5*m11) - (m7*m9);
	t3 = (m5*m10) - (m6*m9);
	
	// d = -( b(tg) - c(th) + d(ti) )
	tmp.m3 = -( (m1*t1) - (m2*t2) + (m3*t3));
	
	// load		NO		(5)		GHINO
	t4 = (m4*m11) - (m7*m8);
	t5 = (m4*m10) - (m6*m8);
	
	// h = a(tg) - c(tn) + d(to)
	tmp.m7 = (m0*t1) - (m2*t4) + (m3*t5);
	
	// unload	G		(4)		-HINO
	// load		Q		(5)		QHINO
	t1 = (m4*m9) - (m5*m8);
	
	// m = -( a(th) - b(tn) + d(tq))
	tmp.m11 = -((m0*t2) - (m1*t4) + (m3*t1));
	
	// unload	HN		(3)		Q-I-O
	// q = a(ti) - b(to) + c(tq)
	tmp.m15 = (m0*t3) - (m1*t5) + (m2*t1);
	
	return tmp;
}

void Matrix::Inverse( Matrix &out ) 
{
	Matrix tmp;
	float det = Determinant();
	if(fabs(det) < 0.0001)
	{
		// do nothing, Matrix is not invertable
	}
	else
	{
		tmp = GetAdjugate();
		tmp /= det;
	}

	out = tmp;
}

void Matrix::setScaleMatrix(Vect4D *scale)
{
	//	{	sx		0		0		0	}
	//	{	0		sy		0		0	}
	//	{	0		0		sz		0	}
	//	{	0		0		0		1	}
	
	//Matrix tmp;
	this->m0 = scale->x;
	this->m1 = 0;
	this->m2 = 0;
	this->m3 = 0;
	
	this->m4 = 0;
	this->m5 = scale->y;
	this->m6 = 0;
	this->m7 = 0;
	
	this->m8 = 0;
	this->m9 = 0;
	this->m10 = scale->z;
	this->m11 = 0;
	
	this->m12 = 0;
	this->m13 = 0;
	this->m14 = 0;
	this->m15 = 1;
}

void Matrix::setRotZMatrix(float az)
{
	//	{	cos		-sin	0		0	}
	//	{	sin		cos		0		0	}
	//	{	0		0		1		0	}
	//	{	0		0		0		1	}
	
	Matrix tmp;
	tmp.m0 = cos(az);
	tmp.m1 = -sin(az);
	tmp.m2 = 0;
	tmp.m3 = 0;
	
	tmp.m4 = sin(az);
	tmp.m5 = cos(az);
	tmp.m6 = 0;
	tmp.m7 = 0;
	
	tmp.m8 = 0;
	tmp.m9 = 0;
	tmp.m10 = 1;
	tmp.m11 = 0;
	
	tmp.m12 = 0;
	tmp.m13 = 0;
	tmp.m14 = 0;
	tmp.m15 = 1;
	
	*this = tmp;
}

// --- End of File ---

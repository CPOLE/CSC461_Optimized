//---------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//---------------------------------------------------------------

#ifndef MATRIX_H
#define MATRIX_H

// includes
#include "Enum.h"
#include "Vect4D.h"

// forward declare
class Vect4D;

// class
class Matrix
{
public:

	// local enumerations
	enum class MatrixRow
	{
		MATRIX_ROW_0,
		MATRIX_ROW_1,
		MATRIX_ROW_2,
		MATRIX_ROW_3
	};

	Matrix();	
	Matrix( Matrix& t);	
	~Matrix();

	//void set( MatrixRow row, Vect4D *t);
	//void get( MatrixRow row, Vect4D *vOut);

	void setIdentMatrix();
	void setTransMatrix( Vect4D *t );
	void setScaleMatrix( Vect4D *s );
	void setRotZMatrix(float Z_Radians );

	//float &operator[](Index e);
	
	Matrix operator*(Matrix &t);
	Matrix operator*(float s );

	float Determinant();
	
	Matrix GetAdjugate();
	Matrix& operator/=( float t);
	
	void Inverse(Matrix &out);
	
//private:
	/*
	// ROW 0
	double m0;
	double m1;
	double m2;
	double m3;

	// ROW 1
	double m4;
	double m5;
	double m6;
	double m7;

	// ROW 2
	double m8;
	double m9;
	double m10;
	double m11;

	// ROW 3
	double m12;
	double m13;
	double m14;
	double m15;
	*/
	union
	{
		struct
		{
			Vect4D v0;
			Vect4D v1;
			Vect4D v2;
			Vect4D v3;
		};

		struct
		{
			// ROW 0
			float m0;
			float m1;
			float m2;
			float m3;
			// ROW 1
			float m4;
			float m5;
			float m6;
			float m7;
			// ROW 2
			float m8;
			float m9;
			float m10;
			float m11;
			// ROW 3
			float m12;
			float m13;
			float m14;
			float m15;
		};
	};
};

#endif  

// --- End of File ---

//---------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//---------------------------------------------------------------

#ifndef Vect4D_H
#define Vect4D_H

// includes
#include "Enum.h"
#include <xmmintrin.h>

// Foward Declarations
class Matrix;

// class
class Vect4D
{
public:
	friend class Matrix;

	Vect4D();
	Vect4D(float tx, float ty, float tz, float tw = 1);
	//	
	Vect4D(__m128 m);
	~Vect4D();

	void Cross(Vect4D &vin, Vect4D &vout);
	float &operator[](Vect e);
	void norm(Vect4D &out);
	void set(float tx, float ty, float tz, float tw = 1);

	Vect4D operator* (float scale);
	Vect4D operator- (Vect4D t);
	Vect4D operator+ (Vect4D t);

//private:
	/*
	double x;
	double y;
	double z;
	double w;
	*/
	union
	{
		__m128	_m;

		struct
		{
			float x;
			float y;
			float z;
			float w;
		};
	};
};

#endif

// --- End of File ---

//-----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#include "Vect.h"

// ----------------------------------
// MODIFY this file
// ----------------------------------
bool Vect::operator < (const Vect& v) const
{
	if (a < v.a) {
		return true;
	}
	else if (a == v.a) {
		//	A=A, Compare B
		if (b < v.b) {
			return true;
		}
		else if (b == v.b) {
			//	B=B, Compare C
			return c < v.c ? true : false;
		}
		else return false;
	}
	else return false;
}

// ---  End of File ---

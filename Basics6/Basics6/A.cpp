//-----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#include <vector>
#include <algorithm>

#include "A.h"

int A[] = 
{
	6,
	7,
	3,
	2,
	8,
	1,
	9,
	4
};

int JunkDataA(777);

void Problem_A( std::vector<int> &UnitTest_A_orig, 
				std::vector<int> &UnitTest_A_insert, 
				std::vector<int> &UnitTest_A_sort)
{
	// ----------------------------------------------------
	// a) Load the A[] data into a vector
	//    Name the vector: A_Vector
	// ----------------------------------------------------
	std::vector<int> A_Vector{A[0], A[1], A[2], A[3], A[4], A[5], A[6], A[7]};
	// ---------------------------------------------------------------------
	// Copies STL to gobal for unit test (Do NOT Remove or modify next line)
	// ---------------------------------------------------------------------
	UnitTest_A_orig.assign(A_Vector.begin(), A_Vector.end());

	// ----------------------------------------------------
	// b) Insert the number '5' between '2' and '8' values into A_Vector
	//    No brute force, assume there are 1000000 numbers before "2" and after "8".
	//    No iterative, simple approach, use the appropriate STL calls for efficiency
	// ----------------------------------------------------
	for (std::vector<int>::iterator it = A_Vector.begin(); it != A_Vector.end(); ++it) {
		if (*it == 8) {
			A_Vector.insert(it, 5);
			break;
		}
	}
	// ---------------------------------------------------------------------
	// Copies STL to gobal for unit test (Do NOT Remove or modify next line)
	// ---------------------------------------------------------------------
	UnitTest_A_insert.assign(A_Vector.begin(), A_Vector.end());

	// ----------------------------------------------------
	// c) sort the A_Vector
	//          Smallest to largest order
	// ----------------------------------------------------
	// ADD CODE HERE:
	sort(A_Vector.begin(), A_Vector.end());

	// ---------------------------------------------------------------------
	// Copies STL to gobal for unit test (Do NOT Remove or modify next line)
	// ---------------------------------------------------------------------
	UnitTest_A_sort.assign(A_Vector.begin(), A_Vector.end());
}

// ---  End of File ---

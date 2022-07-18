//-----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#include <list>
#include <algorithm>
#include <functional>
#include <vector>

#include "B.h"

int B[] = 
{
	66,
	77,
	33,
	22,
	88,
	11,
	99,
	44
};

int JunkDataB(555);

void Problem_B(	std::vector<int> &UnitTest_B_orig, 
				std::vector<int> &UnitTest_B_insert, 
				std::vector<int> &UnitTest_B_sort)
{
	// ----------------------------------------------------
	// a) Load the B[] data into a list
	//    Name the list: B_List
	// ----------------------------------------------------
	// ADD CODE HERE:
	std::list<int> B_List{B[0], B[1], B[2], B[3], B[4], B[5], B[6], B[7]};
	// ---------------------------------------------------------------------
	// Copies STL to gobal for unit test (Do NOT Remove or modify next line)
	// ---------------------------------------------------------------------
	UnitTest_B_orig.assign(B_List.begin(), B_List.end());

	// ----------------------------------------------------
	// b) Insert the number '55' between 22 and 88 into B_List
	//    No brute force, assume there are 1000000 numbers before 22 and after 88.
	//    No iterative, simple approach, use the appropriate STL calls for efficiency
	// ----------------------------------------------------
	for (std::list<int>::iterator it = B_List.begin(); it != B_List.end(); ++it) {
		if (*it == 88) {
			B_List.insert(it, 55);
			break;
		}
	}
	// ---------------------------------------------------------------------
	// Copies STL to gobal for unit test (Do NOT Remove or modify next line)
	// ---------------------------------------------------------------------
	UnitTest_B_insert.assign(B_List.begin(), B_List.end());

	// ----------------------------------------------------
	// c) sort the list in reverse order using the built in functional functions
	//        Largest to Smallest
	// ----------------------------------------------------
	B_List.sort();
	B_List.reverse();
	// ---------------------------------------------------------------------
	// Copies STL to gobal for unit test (Do NOT Remove or modify next line)
	// ---------------------------------------------------------------------
	UnitTest_B_sort.assign(B_List.begin(), B_List.end());
}

// ---  End of File ---

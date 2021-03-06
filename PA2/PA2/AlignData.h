//-----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#ifndef ALIGN_DATA_H
#define ALIGN_DATA_H

// -----------------------------------------------------------
// Add default constructor to each structure
// Initialize all variables to 0
// Do NOT rearrange any data layout...
// These are the classes used with Align::PrintMe();
// -----------------------------------------------------------

struct A
{
	A();
	int  a0;
	char a1;
};

struct B
{
	B();
	float b0;
	float b1;
	bool  b2;
	float b3;
};

struct C
{
	C();
	char   c0;
	double c1;
	char   c2;
};

struct D
{
	D();
	A      d0;
	double d1;
	B      d2;
	char   d3;
	C      d4;
};

struct E
{
	E();
	A    a0;
	C    c0;
	char aa;
	B    b0;
};

#endif

// ---  End of File ---


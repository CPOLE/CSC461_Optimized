//-----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#ifndef REWORK_DATA_H
#define REWORK_DATA_H

//	16 (8)
struct DataA
{
	double r;	//	8
	char a;		//	1
	char b;
	char pad1;
	char pad2;
	char pad3;
	char pad4;
	char pad5;
	char pad6;
};

//	24 (8)
struct DataB
{
	DataA da;	//	16
	int i;		//	4
	char a;		//	1
	char b;
	char pad1;
	char pad2;
};

//	12 (4)
struct DataC
{
	int j;	//	4
	int i;
	char a;	//	1
	bool f;
	char pad1;
	char pad2;
};

//	16 (8)
struct DataD
{
	double r;	//	8
	int i;		//	4
	char a;		//	1
	char b;
	char pad1;
	char pad2;
};

//	32 (8)
struct DataE
{
	double r;		//	8
	int x;			//	4
	int* p;
	char name[12];	//	12 (1)
	char a;			//	1
	char c;
	char pad1;
	char pad2;
};

//	20 (4)
struct Vect
{
	float vx;	//	4
	float vy;
	float vz;
	float vw;
	char a;		//	1
	char b;
	char pad1;
	char pad2;
};

//	32 (4)
struct DataF
{
	Vect v;		//	20 (4)
	int j;		//	4
	int i;
	char c;		//	1
	char b;
	char pad1;
	char pad2;
};

//	56 (8)
struct DataG
{
	DataA a0;	//	16 (8)
	double d0;	//	8
	double d1;
	Vect v;		//	20 (4)
	char b0;	//	1
	char c0;
	char pad1;
	char pad2;
};



#endif

// ---  End of File ---


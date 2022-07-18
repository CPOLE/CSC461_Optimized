//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef NYBLE_H
#define NYBLE_H

// Feel free to add extra methods in the class
// You need to explicitly define and implement the Big four operators
// Do not add extra data in class
// Do not add code here (that goes in *.cpp)

class Nyble
{
public:
	// insert your code here
	Nyble();
	Nyble(unsigned int);
	Nyble(const Nyble& n);
	Nyble& operator = (const Nyble& n);
	~Nyble();
	unsigned char getData();

private:
        // Do not change this data
	unsigned char data;

};

#endif

//---  End of File ---

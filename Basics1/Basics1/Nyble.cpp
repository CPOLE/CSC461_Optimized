//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "Nyble.h"

Nyble::Nyble()
	: data(0) {}

Nyble::Nyble(unsigned int i)
{
	const unsigned int mask = 0x000F;
	unsigned int nyb = i & mask;
	this->data = (unsigned char)nyb;
}

Nyble::Nyble(const Nyble& n)
	: data(n.data) {}

Nyble& Nyble::operator = (const Nyble& n)
{
	this->data = n.data;
	return *this;
}

Nyble::~Nyble() {}
unsigned char Nyble::getData()
{
	return this->data;
}


//---  End of File ---

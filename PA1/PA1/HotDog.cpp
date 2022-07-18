//-----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#include "HotDog.h"

// -----------------------------------------------
// AZUL_REPLACE_ME_STUB
// this is place holder for compiling purposes
// Delete each AZUL_REPLACE_ME_STUB line
// Replace with your own code
// -----------------------------------------------

//	Big 4
HotDog::HotDog()
	: condiments(0), prev(nullptr), next(nullptr)
{
	//
}

HotDog::HotDog(const HotDog& h)
	: condiments(h.condiments), prev(nullptr), next(nullptr)
{
	//
}

HotDog& HotDog::operator = (const HotDog& h)
{
	this->condiments = h.condiments;
	this->prev = nullptr;
	this->next = nullptr;
	return *this;
}

HotDog::~HotDog()
{
	//
}

// Methods
void HotDog::Minus(const Condiments condiment)
{
	// Only use bit-wise operations
	this->condiments = condiments & ~(unsigned int)condiment;
}

void HotDog::Add(const Condiments condiment)
{
	// Only use bit-wise operations
	this->condiments = condiments | (unsigned int)condiment;
}

unsigned int HotDog::GetCondiments() const
{
	return this->condiments;
}

HotDog * const HotDog::GetNext() const
{
	return this->next;
}

HotDog * const HotDog::GetPrev() const
{
	return this->prev;
}

void HotDog::SetNext(HotDog *pDog)
{
	this->next = pDog;
}

void HotDog::SetPrev(HotDog *pDog)
{
	this->prev = pDog;
}


// ---  End of File ---------------


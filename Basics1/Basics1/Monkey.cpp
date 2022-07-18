//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "Monkey.h"
#include <cstring>

//	
int Monkey::numStringsCreated = 0;
int Monkey::numStringsDestroyed = 0;

Monkey::Monkey()
	: x(888), y(999)
{
	this->pStatus = new char[54]{ "This string was initialized by a default constructor!" };
	this->numStringsCreated++;
}

Monkey::Monkey(int _x, int _y)
	: x(_x), y(_y)
{
	this->pStatus = new char[54]{ "ThIs tring was initilized by a clever user!" };
	this->numStringsCreated++;
}


Monkey::Monkey(const Monkey& m)
	: x(m.x), y(m.y)
{
	//char mStatus[54] = " ";
	this->pStatus = new char[54];
	strcpy_s(this->pStatus, 54, m.pStatus);
	this->numStringsCreated++;
}

Monkey& Monkey::operator = (const Monkey& m)
{
	if (this == &m)
		return *this;

	delete[] pStatus;
	this->numStringsDestroyed++;
	this->x = m.x;
	this->y = m.y;
	this->pStatus = new char[54];
	strcpy_s(pStatus, 54, m.pStatus);
	this->numStringsCreated++;
	return *this;
}

Monkey::~Monkey()
{
	numStringsDestroyed++;
	delete[] pStatus;
}

int Monkey::getX()
{
	return this->x;
}

int Monkey::getY()
{
	return this->y;
}

char *Monkey::getStatus()
{
	return this->pStatus;
};

void Monkey::printStatus()
{
	Trace::out("Monkey (Status): %s\n", this->pStatus);
}


//---  End of File ---

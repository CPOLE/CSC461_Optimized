//--------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//--------------------------------------------------------

#include "CopyToBuffer.h"

// retrieve the message
char * Dog::GetMessage()
{
	return this->buff;
}
	
// user sets the message
void Dog::SetMessage( const char * const inMessage )
{
	// Do the copy to internal variable buff
	// make sure it's safe
	// ----> do work here
	memset(this->buff, NULL, BUFF_SIZE);
	uint32_t i = 0;
	uint32_t len = 0;
	if (inMessage > 0) {
		len = strlen(inMessage);
		len = len < BUFF_SIZE ? len : BUFF_SIZE-1;
		while (inMessage[i] != NULL && i < len) {
			this->buff[i] = inMessage[i];
			i++;
		}
	}
	this->buff[i] = NULL;

}

// prints the mesage
void Dog::Print()
{
	Trace::out2("message: %s\n",this->buff);
}

Dog::Dog()
{
	memset( this->buff, 0xaa, BUFF_SIZE );
}

Dog::~Dog()
{
	memset( this->buff, 0xaa, BUFF_SIZE );
}


// ---  End of File ---

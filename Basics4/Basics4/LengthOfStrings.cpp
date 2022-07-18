//--------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//--------------------------------------------------------

#include"LengthOfStrings.h"

size_t LengthOfString_1( const char  * const input)
{
	// using strlen()
	return strlen(input);
}

size_t LengthOfString_2( const char  * const input)
{
	// using char by char
	int len = 0;
	if (input > 0) {
		while (input[len] != NULL) {
			len++;
		}
	}
	return (size_t)len;

}


// ---  End of File ---


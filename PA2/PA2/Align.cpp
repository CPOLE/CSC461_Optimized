//-----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#include "Align.h"

//-------------------------------------------------------------
// PrintME()
//
// Write your alignment printing function here
//-------------------------------------------------------------


Align::Info Align::PrintME(void* pData, int StructSize, char* pString)
{
	Info info;
	info.NumBytesOfPadding = 0;
	info.NumTotalBytes = StructSize;

	unsigned char* pChar = (unsigned char*)pData;
	//
	Trace::out2("%s: \n", pString);
	for (int i = 0, j = 0; i < StructSize; i+= 4) {
		Trace::out2("  0x%02x:", i);
		for (int k = 0; k < 4; j++, k++) {
			Trace::out2(" %02x", (unsigned int)(unsigned char)pChar[j]);
			if (pChar[j] != 0) {
				info.NumBytesOfPadding++;
			}
		}
		Trace::out2("\n");
	}
	Trace::out2("------------------------\n");
	Trace::out2("size : %d  padding : %d\n\n", info.NumTotalBytes, info.NumBytesOfPadding);

	return info;
}

// ---  End of File ---


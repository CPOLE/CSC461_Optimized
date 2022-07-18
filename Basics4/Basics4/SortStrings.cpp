//--------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//--------------------------------------------------------

#include "SortStrings.h"


void ReorderAlphabetical(const char * const inString, char * const outString )
{
	// 1) reorder the words in the string, words are separated with spaces
	// 2) sort words on alphabetical order, (a begin, z end)
	// 3) you don't know how many words 
	// 4) if dynamically create any buffers inside this routine, clean them up
	// 5) use strtok and strcat in your answer
	// 6) YOU need to use qsort() - might be a good function to know
	
	//	count spaces / find number of words
	uint32_t cnt = 0;
	for (int i = 0; inString[i] != '\0'; i++) {
		if (inString[i] == ' ')
			cnt++;
	}
	cnt++;
	
	//	copy array
	char* inStrCopy = new char[strlen(inString) + 1];
	memcpy(inStrCopy, inString, strlen(inString) + 1);

	//	build array of words
	char* words = new char[cnt];
	char* next;
	char* word;

	word = strtok_s(inStrCopy, " ", &next);
	for (uint32_t j = 0; j < cnt; j++) {
		words[j] = *word;
		word = strtok_s(NULL, " ", &next);
	}

}



void ReorderWordLength(const char * const inString, char * const outString )
{
	// 1) reorder the words in the string, words are separated with spaces
	// 2) sort words on their word length order, (short, longest)
	// 3) you don't know how many words 
	// 4) if dynamically create any buffers inside this routine, clean them up
	// 5) use strtok and strcat in your answer
	// 6) You need to use qsort() - might be a good function to know

	AZUL_REPLACE_ME(outString);
	AZUL_REPLACE_ME(inString);
}


// ---  End of File ---

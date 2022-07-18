//---------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//---------------------------------------------------------------

#include "answerRegistry.h"

#define QuestionAnswer(x,y)  Answer::registerAnswer(0,x,y)

unsigned char data[] =
{ 
  0xEB, 0xCD, 0x22, 0x4F,
  0x73, 0xB5, 0xF3, 0x35,
  0x23, 0x24, 0x01, 0xFE,
  0xCD, 0xE3, 0x44, 0x85,
  0x66, 0x43, 0x75, 0x33,
  0x39, 0x5C, 0x22, 0x11,
  0x56, 0xA8, 0xAA, 0x13,
  0x64, 0x82, 0x68, 0x26 
};


void Students_PointerWalk()
{
	// STARTING:
	unsigned char* p;  // char are 8-bits long
	p = &data[0];
	unsigned char* q = (p + 3);
	q = (2 + p);
	
	// Q0:
	//    what value is p[0]?
	// Q1:
	//    what value is *(p+3)?
	// Q2:
	//    what value is *(2+p)?

	QuestionAnswer( 0, 235);
	QuestionAnswer( 1, 79);
	QuestionAnswer( 2, 34);

	// Continuing (leaving the pointer where it is)
	p = p + 12;
	q = (p);
	unsigned char x = p[3];
	p++;
	
	// Q3:
	//   what is value *(p)?
	// Q4:
	//   what is value p[3]?
	// Q5:
	//   what is value *p++?

	QuestionAnswer(3, 205);
	QuestionAnswer(4, 133);
	QuestionAnswer(5, 227);

	// Continuing (leaving the pointer where it is)
	p += 6;
	--p;
	x = p[3];
	
	// Q6:
	//   what is value *--p?
	// Q7:
	//   what is value p[3]?

	QuestionAnswer(6, 117); // 51
	QuestionAnswer(7, 92);

	// Continuing (leaving the pointer where it is)
	//
	p = p + 1;
	p++;
	q = (p + 3);
	//
	// Q8:
	//   what is value *p++?
	// Q9:
	//   what is value *(p + 3)?

	QuestionAnswer(8, 57);
	QuestionAnswer(9, 17);

	// Continuing (leaving the pointer where it is)
	p = 5 + p;
	p++;
	--p;
	// Q10:
	//   what is value *(p++)?
	// Q11:
	//   what is value *(--p)?

	QuestionAnswer(10, 170);
	QuestionAnswer(11, 168);

	// STARTING:
	unsigned int* r;  // ints are 32-bits long
	r = (unsigned int*)&data[0];
	unsigned int* w = (r + 3);
	w += 0;

	// Q12:
	//   what is value *(r)?
	// Q13:
	//   what is value *(r + 3)?

	QuestionAnswer(12, 1327681003);
	QuestionAnswer(13, 2235884493);

	// Continuing (leaving the pointer where it is)
	r++;
	r = r + 2;
	unsigned int t = r[1];
	r = r + 1;
	t = r[0];

	// Q14:
	//   what is value *r++?
	// Q15:
	//   what is value r[1]?
	// Q16:
	//   what is value r[0]?

	QuestionAnswer(14, 905164147);
	QuestionAnswer(15, 863322982);
	QuestionAnswer(16, 863322982);

	// Continuing (leaving the pointer where it is)
	unsigned short *s;  // shorts are 16-bits long
	s = (unsigned short*)r;
	unsigned short k = s[-3];
	s = s - 3;
	k = s[2];
	s += 5;
	k = *(s + 3);

	// Q17:
	//   what is value s[-3]?
	// Q18:
	//   what is value s[2]?
	// Q19:
	//   what is value *(s + 3)?
	// Q20:
	//   what is value *(s)?

	QuestionAnswer(17, 65025);
	QuestionAnswer(18, 34116);
	QuestionAnswer(19, 5034);
	QuestionAnswer(20, 23609);

	// Continuing (leaving the pointer where it is)
	p = (unsigned char *)s;
	q = (p + 1);
	p += 5;
	x = p[-9];
	--p;
	x = p[0];

	// Q21:
	//   what is value *(p + 1)?
	// Q22:
	//   what is value p[-9]?
	// Q23:
	//   what is value p[0]?

	QuestionAnswer(21, 92);
	QuestionAnswer(22, 102);
	QuestionAnswer(23, 86);

}

// --- End of File ---


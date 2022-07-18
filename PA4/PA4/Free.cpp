//-----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#include "Used.h"
#include "Free.h"
#include "Type.h"

// Add magic here
Free::Free(uint32_t BlockSize)
	: mType(Type::FREE), bAboveFree(false), mDataSize((uint16_t)BlockSize), pNext(nullptr), pPrev(nullptr)
{

}
// ---  End of File ---

//-----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#ifndef MEM_H
#define MEM_H

#include "Heap.h"

class Mem
{
public:
	static const uint32_t TotalSize = (50 * 1024);
	static const uint32_t HeapAlign = 16;
	static const uint32_t HeapAlignMask = HeapAlign - 1;
	static const uint32_t HeaderGuards = 64;

	enum class Guard
	{
		Type_A,
		Type_5
	};

public:

	Mem(Guard type);

	Mem() = delete;
	Mem(const Mem&) = delete;
	Mem& operator = (const Mem&) = delete;
	~Mem();

	// implement these functions
	void free(void* const data);
	void* malloc(const uint32_t size);
	void initialize();

	// helper functions
	Heap* GetHeap();
	void Print(int count);

private:
	uint32_t privGetBottom() const;
	uint32_t privGetTop() const;
	void addUsedBlock(Used* newUsed);
	void removeFreeBlock(Free* oldFree);
	void addFreeBlock(Free* newFree);
	void removeUsedBlock(Used* oldUsed);
	void addSecretPointer(Free* newFree);
	Free* mergeDown(Used* oldUsed, Free* belowFree);
	Free* mergeUp(Free* newlyFree, Free* aboveFree);
	void updateBelow(Type aboveBlockType, void* block);

	//	Useful in malloc and free
	Heap* poHeap;

	//	Below: 
	//	Not used in malloc, free, or initialize
	Guard type;
	void* poRawMem;
};

#endif 

// ---  End of File ---


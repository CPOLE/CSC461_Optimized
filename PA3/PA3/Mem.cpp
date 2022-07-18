//-----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#include "Mem.h"
#include "Heap.h"
#include "Type.h"

// To help with coalescing... not required
struct SecretPtr
{
	Free* pFree;
};

// ----------------------------------------------------
//  Initialized the Memory block:
//  Update the Heap
//  Create a free block
//  Heap structure links to free hdr
//-----------------------------------------------------
void Mem::initialize()
{
	//	Top of Heap Head
	Heap* pHeap = this->poHeap;
	//	Top of Free Head
	Free* pFreeAddr = (Free*)(pHeap + 1);
	//	Allocate space for Free Block (less head)
	uint32_t FreeBlockSize = this->privGetBottom() - (uint32_t)(pFreeAddr + 1);
	//	Create new Free Head/Block
	Free* pFree = new (pFreeAddr) Free(FreeBlockSize);
	//	Update Heap
	pHeap->pUsedHead = nullptr;
	pHeap->pFreeHead = pFree;
	pHeap->pNextFit = pFree;
	pHeap->currNumUsedBlocks = 0;
	pHeap->currUsedMem = 0;
	pHeap->currNumFreeBlocks++;
	pHeap->currFreeMem += FreeBlockSize;
}

// ----------------------------------------------------
//  Do your Magic here:
//  Find a free block that fits
//  Change it to used (may require subdivision)
//  Correct the heap Links (used,free) headers 
//  Update stats
//  Return pointer to block
//-----------------------------------------------------
void* Mem::malloc(const uint32_t _size)
{
	Heap* pHeap = this->poHeap;
	Free* pFree = pHeap->pFreeHead;
	//	Look thru free nodes - need to add
	while (pFree != nullptr) {
		//	----
		//	Perfect fit
		if ((uint32_t)pFree->mDataSize == _size) {
			//	Find block size
			//	uint32_t AllocatedBlockSize = this->privGetBottom() - (uint32_t)(pFree + 1);
			//	Create new block
			Used* pUsed = new (pFree) Used(_size);

			//	---- Make helper method
			//	Add new used to start of list
			pUsed->pPrev = nullptr;
			if (pHeap->pUsedHead != nullptr) {
				//	Declare tmp of old head
				pUsed->pNext = pHeap->pUsedHead;
				pHeap->pUsedHead->pPrev = pUsed;
				pHeap->pUsedHead = pUsed;
			}
			else {
				pUsed->pPrev = nullptr;
				pHeap->pUsedHead = pUsed;
			}

			//	---- Make helper method
			//	---- NEED TO IMPLEMENT
			//	Remove free from list
			pHeap->pFreeHead = nullptr;
			pHeap->pNextFit = nullptr;
			pHeap->currNumUsedBlocks++;
			pHeap->currNumFreeBlocks--;
			pHeap->currUsedMem += _size;
			pHeap->currFreeMem -= _size;

			//	return
			return pUsed + 1;
		}
		//	----
		//	Need to sub-divide
		else if (pFree->mDataSize > _size) {
			//	Remove free from free list
			Free* pFreeTmp = poHeap->pFreeHead;
			//	Check if free is head
			if (pFreeTmp != nullptr && pFreeTmp == pFree) {
				if (pFreeTmp->pNext != nullptr) {
					poHeap->pFreeHead->pNext->pPrev = nullptr;
				}
				//	Update free head
				poHeap->pFreeHead = poHeap->pFreeHead->pNext;
			}
			else {
				while (pFreeTmp != nullptr) {
					if (pFreeTmp == pFree) {
						//	Check if found node is in middle
						if (pFreeTmp->pNext != nullptr) {
							pFreeTmp->pPrev->pNext = pFreeTmp->pNext;
							pFreeTmp->pNext->pPrev = pFreeTmp->pPrev;
						}
						//	Check if found end is at the end
						else {
							pFreeTmp->pPrev->pNext = nullptr;
						}
					}
					else {
						pFreeTmp = pFreeTmp->pNext;
					}
				}
			}

			//	Find end of original free block
			uint32_t pFreeEndLoc = (uint32_t)(pFree + 1) + pFree->mDataSize;
			//	Create Used block
			Used* pUsed = new (pFree) Used(_size);

			//	Find end of used block
			uint32_t pUsedEndLoc = (uint32_t)(pUsed + 1) + pUsed->mDataSize;
			//	Calculate remaining size
			uint32_t RemainingBlockSize = pFreeEndLoc - pUsedEndLoc - sizeof(Free);
			//	Create Free block
			Free* pFreeRemainder = new ((Free*)pUsedEndLoc) Free(RemainingBlockSize);
			//	---- Make helper method
			//	---- NEEDS TO BE INSERTED IN ORDER (?)
			//	---- NEEDS TO BE COASLESCED
			//	Add free to free list
			pFreeRemainder->pPrev = nullptr;
			pFreeRemainder->bAboveFree = false;
			if (pHeap->pFreeHead != nullptr) {
				//	Update pointers
				pFreeRemainder->pNext = pHeap->pFreeHead;
				pFreeRemainder->pNext->pPrev = pFreeRemainder;
			}

			pHeap->pFreeHead = pFreeRemainder;
			pHeap->pNextFit = pFreeRemainder;
			pHeap->currNumUsedBlocks++;
			pHeap->currFreeMem = RemainingBlockSize;

			//	---- Make helper method
			//	Add new used to start of list
			pUsed->pPrev = nullptr;
			if (pHeap->pUsedHead != nullptr) {
				//	Update pointers
				pUsed->pNext = pHeap->pUsedHead;
				pHeap->pUsedHead->pPrev = pUsed;
			}
			pHeap->pUsedHead = pUsed;
			pHeap->currUsedMem += _size;

			//	return
			return pUsed + 1;
		}
		else {
			pFree = pFree->pNext;
		}
	}
	//	No suitable free blocks, return nullptr
	return pFree;
}

// ----------------------------------------------------
//  Do your Magic here:
//  Return the free block to the system
//  May require Coalescing
//  Correct the heap Links (used,free) headers 
//  Update stats
//-----------------------------------------------------
void Mem::free(void* const data)
{
	Heap* pHeap = this->poHeap;
	Used* pUsed = (Used*)data - 1;

	//	Remove used from used list
	//Used* pUsedTmp = pHeap->pUsedHead;
	//	Check if used is head
	if (pHeap->pUsedHead != nullptr && pHeap->pUsedHead == pUsed) {
		if (pHeap->pUsedHead->pNext != nullptr) {
			pHeap->pUsedHead->pNext->pPrev = nullptr;
		}
		//	Update used head
		pHeap->pUsedHead = pHeap->pUsedHead->pNext;
	}
	else {
		while (pHeap->pUsedHead != nullptr) {
			if (pHeap->pUsedHead == pUsed) {
				//	Check if found node is in middle
				if (pHeap->pUsedHead->pNext != nullptr) {
					pHeap->pUsedHead->pPrev->pNext = pHeap->pUsedHead->pNext;
					pHeap->pUsedHead->pNext->pPrev = pHeap->pUsedHead->pPrev;
				}
				//	Check if found end is at the end
				else {
					pHeap->pUsedHead->pPrev->pNext = nullptr;
				}
			}
			else {
				pHeap->pUsedHead = pHeap->pUsedHead->pNext;
			}
		}
	}

	//	Find bottom of used node
	//uint32_t pUsedEndLoc = (uint32_t)(pUsed + 1) + pUsed->mDataSize;
	uint32_t usedBlockSize = (uint32_t)pUsed->mDataSize;
	Free* pNextTmp = (Free*)((uint32_t)(pUsed + 1) + pUsed->mDataSize);
	if ((uint32_t)(pUsed + 1) + pUsed->mDataSize == this->privGetBottom()) {
		//	Create new free block
		Free* pNewFree = new ((Free*)pUsed) Free(pUsed->mDataSize);
		//	Add free block to list
		pNewFree->pPrev = nullptr;
		pNewFree->mType = Type::FREE;
		pNewFree->bAboveFree = false;
		if (pHeap->pFreeHead != nullptr) {
			//	Update pointers
			pNewFree->pNext = pHeap->pFreeHead;
			pNewFree->pNext->pPrev = pNewFree;
		}
		pHeap->currNumFreeBlocks++;
		pHeap->pFreeHead = pNewFree;
		pHeap->pNextFit = pNewFree;
		pHeap->currFreeMem += usedBlockSize;
	}
	else {
		//	Check if below is free - if so, cast free up
		if (pNextTmp->mType == Type::FREE) {
			uint32_t pNextEndLoc = (uint32_t)(pNextTmp + 1) + pNextTmp->mDataSize;
			pNextTmp = (Free*)pUsed;
			uint32_t combinedBlockSize = pNextEndLoc - (uint32_t)(pNextTmp + 1);
			pNextTmp->mDataSize = (uint16_t)combinedBlockSize;
			pNextTmp->mType = Type::FREE;
			pHeap->pFreeHead = pNextTmp;
			pHeap->pNextFit = pNextTmp;
			pHeap->currFreeMem += usedBlockSize + sizeof(Free);
		}
		else {
			//	Create new free block
			Free* pNewFree = new ((Free*)pUsed) Free(pUsed->mDataSize);
			//	Add free block to list
			pNewFree->pPrev = nullptr;
			pNewFree->mType = Type::FREE;
			pNewFree->bAboveFree = false;
			if (pHeap->pFreeHead != nullptr) {
				//	Update pointers
				pNewFree->pNext = pHeap->pFreeHead;
				pNewFree->pNext->pPrev = pNewFree;
			}
			pHeap->currNumFreeBlocks++;
			pHeap->pFreeHead = pNewFree;
			pHeap->pNextFit = pNewFree;
			pHeap->currFreeMem += usedBlockSize;
		}
	}



	pHeap->currNumUsedBlocks--;
	pHeap->currUsedMem -= usedBlockSize;
	//pHeap->currFreeMem += usedBlockSize;

}

uint32_t Mem::privGetBottom() const
{
	return (uint32_t)this->poHeap + Mem::TotalSize;
}



// ---  End of File ---

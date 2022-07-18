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
	this->poHeap->pFreeHead = pFree;
	this->poHeap->pNextFit = pFree;
	this->poHeap->currNumFreeBlocks++;
	this->poHeap->currFreeMem += (FreeBlockSize);
	pHeap->pUsedHead = nullptr;
	pHeap->currNumUsedBlocks = 0;
	pHeap->currUsedMem = 0;
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
	//	Look thru free nodes - need to add
	while (this->poHeap->pNextFit != nullptr) {
		Free* pFree = this->poHeap->pNextFit;
		//	Perfect fit
		if ((uint32_t)pFree->mDataSize == _size) {
			//	Remove Free block
			this->removeFreeBlock(pFree);
			//	Create new Used block
			Used* pUsed = new (pFree) Used(_size);
			//	Add new Used to start of list
			this->addUsedBlock(pUsed);
			//	Return Used block
			return pUsed + 1;
		}
		//	Need to sub-divide
		else if (pFree->mDataSize > _size) {
			//	Find end of Free Block
			uint32_t pFreeEndLoc = (uint32_t)(pFree + 1) + pFree->mDataSize;
			//	Remove Free block
			this->removeFreeBlock(pFree);
			//	Create Used block
			Used* pUsed = new (pFree) Used(_size);
			//	Find end of Used block, calculate remaining Free space
			uint32_t pUsedEndLoc = (uint32_t)(pUsed + 1) + pUsed->mDataSize;
			uint32_t RemainingBlockSize = pFreeEndLoc - (pUsedEndLoc + sizeof(Used));
			//	Create Free block
			Free* pFreeRemainder = new ((Free*)pUsedEndLoc) Free(RemainingBlockSize);
			//	Add Used Block, Free Block to lists
			this->addFreeBlock(pFreeRemainder);
			this->addUsedBlock(pUsed);
			//	Update NextFit
			this->poHeap->pNextFit = pFreeRemainder;
			//	Return Used block
			return pUsed + 1;
		}
		else {
			//	If NextFit is too small, Update NextFit
			this->poHeap->pNextFit = this->poHeap->pNextFit->pNext != nullptr ? this->poHeap->pNextFit->pNext : this->poHeap->pFreeHead;
		}
	}
	//	No suitable free blocks, return nullptr
	return nullptr;
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
	Used* pUsed = (Used*)data - 1;
	//	Find bottom of Used node, calculate Used space
	uint32_t pUsedEndLoc = (uint32_t)(pUsed + 1) + pUsed->mDataSize;
	//	Remove used from used list
	this->removeUsedBlock(pUsed);
	//	Look at Type of below block
	Free* pNextTmp = (Free*)pUsedEndLoc;
	//	If block bottom is (1) free block header and (2) not out of bounds
	if (pUsedEndLoc < this->privGetBottom() && pNextTmp->mType == Type::FREE) {
		//	Remove below Free block
		pNextTmp = this->mergeDown(pUsed, pNextTmp);
	}
	else {
		//	Create/Add new Free block in place of old Used block
		pNextTmp = new ((Free*)pUsed) Free(pUsed->mDataSize);
		this->addFreeBlock(pNextTmp);
	}
	//	Look at Type of below block
	SecretPtr* secret = (SecretPtr*)((uint32_t)pNextTmp - sizeof(SecretPtr));
	//	If above secret (1) points to free block header and (2) isn't out of bounds
	if ((uint32_t)secret > this->privGetTop()) {
		if (((Free*)secret->pFree)->mType == Type::FREE) {
			pNextTmp = this->mergeUp(pNextTmp, secret->pFree);
		}
	}
}

//	--------------------
//	Helper methods
//	--------------------

uint32_t Mem::privGetBottom() const {
	return (uint32_t)this->poHeap + Mem::TotalSize;
}

uint32_t Mem::privGetTop() const {
	return (uint32_t)this->poHeap + sizeof(Heap);
}

void Mem::addUsedBlock(Used* newUsed) 
{
	//	Update linked list
	newUsed->pPrev = nullptr;
	if (this->poHeap->pUsedHead != nullptr) {
		newUsed->pNext = this->poHeap->pUsedHead;
		newUsed->pNext->pPrev = newUsed;
	}
	//	Update Heap data
	this->poHeap->pUsedHead = newUsed;
	this->poHeap->currNumUsedBlocks++;
	this->poHeap->currUsedMem += newUsed->mDataSize;
	//	Set secret pointer
	this->addSecretPointer((Free*)newUsed);
	//	Update below flag
	this->updateBelow(Type::USED, newUsed);
}

void Mem::removeUsedBlock(Used* oldUsed) 
{
	Used* pUsedTmp = this->poHeap->pUsedHead;
	//	Update Used head if removed block is Used head
	if (pUsedTmp == oldUsed) {
		this->poHeap->pUsedHead = poHeap->pUsedHead->pNext;
	}
	//	Update next Used if not end of list
	if (oldUsed->pNext != nullptr) {
		oldUsed->pNext->pPrev = oldUsed->pPrev;
	}
	//	Update prev Used if not start of list
	if (oldUsed->pPrev != nullptr) {
		oldUsed->pPrev->pNext = oldUsed->pNext;
	}
	//	Update Heap data
	this->poHeap->currNumUsedBlocks--;
	this->poHeap->currUsedMem -= oldUsed->mDataSize;
}

void Mem::addFreeBlock(Free* newFree) 
{
	//	Empty list
	if (this->poHeap->pFreeHead == nullptr) {
		this->poHeap->pFreeHead = newFree;
		this->poHeap->pNextFit = newFree;
	}
	//	Insert new Free before current head
	else if ((uint32_t)newFree < (uint32_t)this->poHeap->pFreeHead) {
		newFree->pNext = this->poHeap->pFreeHead;
		newFree->pNext->pPrev = newFree;
		this->poHeap->pFreeHead = newFree;
	}
	else {
		Free* pFreeTmp = this->poHeap->pFreeHead;
		//	Walk list
		while (pFreeTmp->pNext != nullptr && (uint32_t)pFreeTmp->pNext < (uint32_t)newFree) {
			pFreeTmp = pFreeTmp->pNext;
		}
		newFree->pNext = pFreeTmp->pNext;
		//	If new Free inserted in middle
		if (pFreeTmp->pNext != nullptr) {
			newFree->pNext->pPrev = newFree;
		}
		pFreeTmp->pNext = newFree;
		newFree->pPrev = pFreeTmp;
	}
	//	Update Heap data
	this->poHeap->currNumFreeBlocks++;
	this->poHeap->currFreeMem += (newFree->mDataSize);
	//	Set secret pointer
	this->addSecretPointer(newFree);
	//	Update below flag
	this->updateBelow(Type::FREE, newFree);
	//	Update NextFit
	//	this->poHeap->pNextFit = newFree;
}

void Mem::removeFreeBlock(Free* oldFree) 
{
	Free* pFreeTmp = this->poHeap->pFreeHead;
	//	Update Free head if removed block is Free head
	if (pFreeTmp == oldFree) {
		this->poHeap->pFreeHead = poHeap->pFreeHead->pNext;
	}
	//	Update next Free if not end of list
	if (oldFree->pNext != nullptr) {
		oldFree->pNext->pPrev = oldFree->pPrev;
	}
	//	Update prev Free if not start of list
	if (oldFree->pPrev != nullptr) {
		oldFree->pPrev->pNext = oldFree->pNext;
	}
	//	Update Heap data
	this->poHeap->currNumFreeBlocks--;
	this->poHeap->currFreeMem -= oldFree->mDataSize;
	//	Update NextFit if removed block is NextFit - applicable only for Perfect Fit malloc
	if (oldFree == this->poHeap->pNextFit) {
		//	If NextFit isn't at end of Free list, continue; else wrap around to Free head
		this->poHeap->pNextFit = this->poHeap->pNextFit->pNext != nullptr ? this->poHeap->pNextFit->pNext : this->poHeap->pFreeHead;
	}
}

void Mem::addSecretPointer(Free* newFree)
{
	//	Set secret pointer
	uint32_t pSecretLoc = (uint32_t)(newFree + 1) + newFree->mDataSize - sizeof(SecretPtr);
	SecretPtr* secret = new ((SecretPtr*)pSecretLoc) SecretPtr;
	secret->pFree = newFree;
}

Free* Mem::mergeDown(Used* oldUsed, Free* belowFree) {
	//	Remove below Free block
	this->removeFreeBlock(belowFree);
	//	Find size of below Free block
	uint32_t combinedBlockSize = (oldUsed->mDataSize + belowFree->mDataSize + sizeof(Free));
	//	Created "merged" Free block
	Free* pNewFree = new ((Free*)oldUsed) Free(combinedBlockSize);
	//	Add Free block to list
	this->addFreeBlock(pNewFree);
	return pNewFree;
}

Free* Mem::mergeUp(Free* newlyFree, Free* aboveFree) {
	//	Remove below Free block
	this->removeFreeBlock(newlyFree);
	this->removeFreeBlock(aboveFree);
	//	Find size of below Free block
	uint32_t combinedBlockSize = (newlyFree->mDataSize + aboveFree->mDataSize + sizeof(Free));
	//	Created "merged" Free block
	Free* pNewFree = new ((Free*)aboveFree) Free(combinedBlockSize);
	//	Add Free block to list
	this->addFreeBlock(pNewFree);
	return pNewFree;
}

void Mem::updateBelow(Type aboveBlockType, void* block) {
	Free* tmpBlock = (Free*)block;
	uint32_t belowBlock = (uint32_t)(tmpBlock + 1) + tmpBlock->mDataSize;
	if (belowBlock < this->privGetBottom()) {
		((Free*)belowBlock)->bAboveFree = aboveBlockType == Type::FREE ? true : false;
	}
}

// ---  End of File ---
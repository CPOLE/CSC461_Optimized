//-----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

// Users
#include "Bloated.h"
#include "Node.h"
#include "hotcold.h"

HotCold::HotCold(const Bloated* const pBloated)
{
	//	Get bloated listed head - Get node count
	Node* pBloat = pBloated->GetListHead();
	unsigned int nodeCount = this->GetNodeCount(pBloat);

	//	Allocate memory and set HotHead on Hot Stack
	this->pHotHead = new HotNode[nodeCount];
	AZUL_PLACEMENT_NEW_BEGIN
	#undef new
	HotNode* pHot = new (pHotHead) HotNode;
	AZUL_PLACEMENT_NEW_END
	//	Update HotHead prev/next/key
	pHot->pPrev = nullptr;
	pHot->pNext = nullptr;
	pHot->key = pBloat->key;

	//	Allocate Memory for Cold Stack
	this->pColdHead = new ColdNode[nodeCount];

	int hotCnt = 1;
	int coldCnt = 0;
	//	Walk Bloated list - Build HotCold list
	while (pBloat != nullptr) {
		if (pBloat->pNext != nullptr) {
			//	Add new HotNode - Update prev/key
			AZUL_PLACEMENT_NEW_BEGIN
			#undef new
			pHot->pNext = new (pHot + hotCnt) HotNode;
			AZUL_PLACEMENT_NEW_END
			pHot->pNext->pPrev = pHot;
			pHot->pNext->key = pBloat->pNext->key;
		}
		else {
			//	End list
			pHot->pNext = nullptr;
		}
		//	Set on Cold Stack - Use Setter
		AZUL_PLACEMENT_NEW_BEGIN
		#undef new
		pHot->pCold = new (this->pColdHead + coldCnt) ColdNode;
		AZUL_PLACEMENT_NEW_END
		pHot->pCold->SetColdData(pBloat);
		//	Step thru bloated list and hot/cold stacks
		pBloat = pBloat->pNext;
		pHot = pHot->pNext;
		coldCnt++;
	}
}

HotCold::~HotCold()
{
	delete[] pHotHead;
	delete[] pColdHead;
	//pHotHead = nullptr;
}

bool HotCold::FindKey(int key, ColdNode*& pFoundColdNode, HotNode*& pFoundHotNode)
{
	HotNode* pHot = this->pHotHead;
	//	Walk list looking for key
	while (pHot != nullptr) {
		if (pHot->key == key) {
			//	Return pointer to node containing found key
			//	Return true
			*&pFoundHotNode = pHot;
			*&pFoundColdNode = pHot->pCold;
			return true;
		}
		pHot = pHot->pNext;
	}
	return false;
}

HotNode* HotCold::GetHotHead() const
{
	return this->pHotHead;
}

unsigned int HotCold::GetNodeCount(Node* bHead) const
{
	unsigned int cnt = 0;
	Node* pBloat = bHead;
	while (pBloat != nullptr) {
		pBloat = pBloat->pNext;
		cnt++;
	}
	return cnt;
}

// ---  End of File ---


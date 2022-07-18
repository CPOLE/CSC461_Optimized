//-----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

// Users
#include "Bloated.h"
#include "Node.h"
#include "JediHotCold.h"
#include "JediRedirect.h"

JediHotCold::JediHotCold(const Bloated * const pBloated)
{
	//	Heads
	Node* pBloat = pBloated->GetListHead();
	JediHotNode* pjHot;
	JediHotNode* pjHotPrev = nullptr;
	//	Allocate Memory
	unsigned int nodeCount = this->GetNodeCount(pBloat);
	this->pHotHead = new JediHotNode[nodeCount/8];
	this->pColdHead = new JediColdNode[nodeCount];
	this->pRedirectHead = new JediRedirect[nodeCount/8];
	//	Counters
	unsigned int pos = 0;
	unsigned int cold_pos = 0;
	unsigned int key_len = 0;
	unsigned int key_index = 0;

	while (pBloat != nullptr) {
		//	Set up new Hot/Redirect nodes
		AZUL_PLACEMENT_NEW_BEGIN
		#undef new
		pjHot = new (pHotHead + pos) JediHotNode;
		pjHot->pRedirect = new (pRedirectHead + pos) JediRedirect;
		AZUL_PLACEMENT_NEW_END
		//	Update pointers
		pjHot->pPrev = pjHotPrev;
		pjHot->pNext = nullptr;
		if (pjHot->pPrev != nullptr) {
			pjHotPrev->pNext = pjHot;
		}
		//	Get length of key array (fixed at 8?) / res vet key index
		key_len = sizeof(pjHot->key)/4;
		key_index = 0;
		//	
		while (key_index < key_len) {
			AZUL_PLACEMENT_NEW_BEGIN
			#undef new
			pjHot->key[key_index] = pBloat->key;
			pjHot->pRedirect->pCold[key_index] = new (pColdHead + cold_pos) JediColdNode;
			pjHot->pRedirect->pCold[key_index]->SetJediColdData(pBloat);
			AZUL_PLACEMENT_NEW_END
			//	Increment counters
			key_index++;
			cold_pos++;
			pBloat = pBloat->pNext;
		}
		//	Increment counter/update node
		pos++;
		pjHotPrev = pjHot;
		pjHot = pjHot->pNext;
	}
}

JediHotCold::~JediHotCold()
{
	delete[] pHotHead;
	delete[] pColdHead;
	delete[] pRedirectHead;
}

//
bool JediHotCold::FindKey(int key, JediColdNode *&pFoundColdNode, JediHotNode *&pFoundHotNode)
{
	JediHotNode* pjHot = this->pHotHead;
	unsigned int key_len = 0;
	unsigned int key_index = 0;
	//	Walk list looking for key
	while (pjHot != nullptr) {
		key_len = sizeof(pjHot->key)/4;
		key_index = 0;
		//
		while (key_index < key_len) {
			if (pjHot->key[key_index] == key) {
				*&pFoundHotNode = pjHot;
				*&pFoundColdNode = pjHot->pRedirect->pCold[key_index];
				return true;
			} 
			key_index++;
		}
		pjHot = pjHot->pNext;
	}
	return false;
}

JediHotNode *JediHotCold::GetHotHead() const
{
	return this->pHotHead;
}

unsigned int JediHotCold::GetNodeCount(Node* bHead) const
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


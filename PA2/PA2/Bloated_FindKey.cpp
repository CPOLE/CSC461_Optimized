//-----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

// user headers
#include "bloated.h"
#include "Node.h"

//----------------------------------------------------------------------------------
// Find Key using linked lists (pointers only) 
//    Hint: use ->pNext
//    YOU MUST - iterate through the nodes in a linked list fashion or 0 credit
//               starting from the head until you find it
//
// Return true if you find the node
// Return the pointer in the argument list to the node (if found)
//----------------------------------------------------------------------------------

bool Bloated::FindKey(int key, Node *&foundNode) const
{
	Node* pNode = this->pHead;
	//	Walk list looking for key
	while (pNode != nullptr) {
		if (pNode->key == key) {
			//	Return pointer to node containing found key
			//	Return true
			*&foundNode = pNode;
			return true;
		}
		pNode = pNode->pNext;
	}
	return false;
}

// ---  End of File ---


//-----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#ifndef SEARCH_LIST_H
#define SEARCH_LIST_H

#include "Node.h"

class AList;

class SearchList
{
public:
	// ---> CHANGE this value
	static const unsigned int CUT_OFF = 34;

public:
	// Big four
	SearchList() = delete;
	~SearchList();
	SearchList(const SearchList &) = delete;
	SearchList &operator = (const SearchList &) = delete;

	SearchList(AList *pList);

	// Accessors
	Node *GetHead() const;
	void SetHead(Node *pNode);
	int GetNumNodes() const;

	// Class methods
	int GetCutoffLength(); 

	//---------------------------------------------------------------------------------------
	// Please implement(rework) these methods (add additional methods to help if you want)
	//---------------------------------------------------------------------------------------
	void InsertionSort();
	Node* inSort(Node* head);
	void sortedInsert(Node** sortedHead, Node* insertNode);
	void MergeSort();
	Node* mergeSort(Node* head);
	Node* merge(Node* left, Node* right);
	Node* split(Node* head);
	void MergeComboSort(int CutoffLength);
	Node* mergeComboSort(Node* head, int begin, int end, int cutoff);

private:
	// ------------------------------------------------------
	// Data - YOU CANNOT add or change data in this class
	// ------------------------------------------------------

	Node *pHead;
	int  NumNodes;
	int  mCutoffLength;
};

#endif 

// ---  End of File ---

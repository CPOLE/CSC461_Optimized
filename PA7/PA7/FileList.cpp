//-----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#include "AList.h"
#include "Node.h"
#include "FileList.h"

// --------------------------------
// -->    MODIFY This FILE    <----
// --------------------------------

FileList::FileList()
: pHead(nullptr),
NumNodes(0)
{
	// Hint you might need to rework this...
	// if you add data to FileList class
}

FileList::~FileList()
{
	free(this->pHead);
}

void FileList::WriteToFile(const char * const pFileName, AList *pAList)
{
	// Everyone - Fill in your CustomDestructCommand::Command() that will be used in the destructor
	Node* curr = pAList->GetHead();
	FILE* pFileHandle;
	//	open
	fopen_s(&pFileHandle, pFileName, "wb");
	//	write to file
	while (curr) {
		fwrite(curr, 4, 6, pFileHandle);
		curr = curr->pNext;
	}
	//	close
	fclose(pFileHandle);
}

FileList::FileList(const char * const pFileName, int numNodes)
{
	// Everyone - Fill in your CustomDestructCommand::Command() that will be used in the destructor.
	//	new list
	FILE* pFileHandle;
	fopen_s(&pFileHandle, pFileName, "rb");
	Node* curr = (Node*)malloc(sizeof(Node)*numNodes+sizeof(FileList));
	fread(curr, sizeof(int), 6, pFileHandle);
	curr->pPrev = nullptr;
	curr->pNext = curr + 1;
	this->pHead = curr;
	Node* prev = curr;
	curr = curr->pNext;

	//	populate list
	for (int i = 1; i < numNodes; i++) {
		fread(curr, sizeof(int), 6, pFileHandle);
		curr->pPrev = prev;
		curr->pNext = curr + 1;
		prev = curr;
		curr = curr->pNext;
	}

	//	close
	fclose(pFileHandle);
}

// ---  End of File ---

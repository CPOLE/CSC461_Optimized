//-----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#include "Boustrophedonic.h"

void Remove(Node *&pHead, int row, int col)
{
	Node* tmp = pHead;
	int rowNum = 0;
	int colNum = 0;

	//	CAN REMOVE COL# / INCREMENT / DECREMENT / JUST TRAVERSE WHILE NOT NULL AND WHEN CORRECT ROW IS FOUND USE FOR LOOP TO ITERATE TO CORRECT COLUMN

	//	walk to correct row:
	while (rowNum != row)
	{
		//	even row, walk east:
		if (rowNum % 2 == 0) {
			while (tmp->pEast != nullptr) {
				tmp = tmp->pEast;
				colNum++;
			}
			//	step south:
			tmp = tmp->pSouth;
			rowNum++;
		}
		//	odd row, walk west:
		else {
			while (tmp->pWest != nullptr) {
				tmp = tmp->pWest;
				colNum--;
			}
			//	step south
			tmp = tmp->pSouth;
			rowNum++;
		}
	}

	//	walk to correct column:
	//	desired column is east, walk east:
	while (col > colNum) {
		tmp = tmp->pEast;
		colNum++;
	}
	//	desired column is east, walk east:
	while (col < colNum) {
		tmp = tmp->pWest;
		colNum--;
	}

	//	update neighbors:

	//	even row, even col:
	if (row % 2 == 0 && col % 2 == 0)
	{
		//	find neighbors:
		Node* east = tmp->pEast;
		Node* south = east->pSouth != nullptr ? east->pSouth->pWest : nullptr;
		Node* north = east->pNorth != nullptr ? east->pNorth->pWest : nullptr;
		Node* west;

		//	update head if necessary
		if (col == 0) {
			west = nullptr;
			pHead = east;
		}

		//	if only 1 row:
		if (south == nullptr && north == nullptr) {
			int neighborColNum = 0;
			west = pHead;
			while (west != nullptr && neighborColNum < col - 1) {
				west->pEast = tmp->pEast;
				neighborColNum++;
			}
		}
		//	multiple rows - south or north will result:
		else {
			if (south != nullptr) {
				west = south->pWest != nullptr ? south->pWest->pWest->pNorth->pEast : nullptr;
			}
			else {
				west = north->pWest != nullptr ? north->pWest->pWest->pSouth->pEast : nullptr;
			}
		}
		//	update neighbors:
		if (south != nullptr) south->pNorth = north;
		if (north != nullptr) north->pSouth = south;
		if (west != nullptr) west->pEast = east;
	}

	//	odd row, odd col:
	else if (row % 2 == 1 && col % 2 == 1)
	{
		//	find neighbors:
		Node* west = tmp->pWest;
		Node* south = west->pSouth != nullptr ? west->pSouth->pEast : nullptr;
		Node* north = west->pNorth != nullptr ? west->pNorth->pEast : nullptr;
		Node* east;
		//	multiple rows - south or north will result (because odd row):
		if (south != nullptr) {
			east = south->pEast != nullptr ? south->pEast->pEast->pNorth->pWest : nullptr;
		}
		else {
			east = north->pEast != nullptr ? north->pEast->pEast->pSouth->pWest : nullptr;
		}
		//	update neighbors:
		if (north != nullptr) north->pSouth = south;
		if (south != nullptr) south->pNorth = north;
		if (west != nullptr) west->pEast = east;
	}

	//	even row/odd col:
	else if (row % 2 == 0 && col % 2 == 1)
	{
		//	find neighbors:
		Node* east = tmp->pEast != nullptr ? tmp->pEast : nullptr;
		Node* south = tmp->pSouth != nullptr ? tmp->pSouth : nullptr;
		Node* north = tmp->pNorth != nullptr ? tmp->pNorth : nullptr;
		Node* west;
		//	if only 1 row:
		if (south == nullptr && north == nullptr) {
			int neighborColNum = 0;
			west = pHead;
			while (west != nullptr && neighborColNum < col - 1) {
				west->pEast;
				neighborColNum++;
			}
		}
		//	multiple rows - south or north will result:
		else {
			if (south != nullptr) {
				west = south->pWest->pNorth;
			}
			else {
				west = north->pWest->pSouth;
			}
		}
		//	update neighbor:
		west->pEast = east;
	}

	//	odd row/even col:
	else 
	{
		//	find neighbors:
		Node* north = tmp->pNorth;
		Node* east = north->pEast->pSouth;
		Node* west = tmp->pWest;
		//	update neighbor:
		east->pWest = west;
	}

	delete tmp;
}

// ---  End of File ---------------

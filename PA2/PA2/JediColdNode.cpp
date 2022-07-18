//-----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#include "Node.h"
#include "JediColdNode.h"

// Insert code
void JediColdNode::SetJediColdData(Node* pBloat)
{
	this->key = pBloat->key;
	this->aa = pBloat->aa;
	this->bb = pBloat->bb;
	this->cc = pBloat->cc;
	this->dd = pBloat->dd;
	this->x = pBloat->x;
	this->y = pBloat->y;
	this->z = pBloat->z;
	this->w = pBloat->w;
	this->A = pBloat->A;
	this->B = pBloat->B;
	this->C = pBloat->C;
	this->D = pBloat->D;
	this->MA = pBloat->MA;
	this->MB = pBloat->MB;
	this->MC = pBloat->MC;
	this->MD = pBloat->MD;
	this->ME = pBloat->ME;
	memcpy(this->name, pBloat->name, Node::NAME_SIZE);
}

// ---  End of File ---


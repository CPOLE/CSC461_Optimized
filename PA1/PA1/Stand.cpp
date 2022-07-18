//-----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#include "Stand.h"

// -----------------------------------------------
// AZUL_REPLACE_ME_STUB
// this is place holder for compiling purposes
// Delete each AZUL_REPLACE_ME_STUB line
// Replace with your own code
// -----------------------------------------------

// Methods
Stand::Stand()
	: head(nullptr), currentOrders(0), peakOrders(0)
{
	//
}

Stand::~Stand()
{
	while (this->head != nullptr)
	{
		Order* tmp = this->head->GetNext();
		delete head;
		head = tmp;
	}
}

int Stand::GetCurrOrders() const
{
	return this->currentOrders;
}

int Stand::GetPeakOrders() const
{
	return this->peakOrders;
}

Order * const Stand::GetHead()
{
	return this->head;
}

void Stand::Remove(const Name name)
{
	if (this->head == nullptr) {
		return;
	}

	Order* tmp = head;
	Order* orderToDelete;
	this->currentOrders--;

	//	Update linked list pointers
	//	Check head
	if (tmp->GetName() == name) {
		//	Mark for deletion
		orderToDelete = tmp;
		//	Check if name is in head
		if (tmp->GetNext() != nullptr) {
			tmp->GetNext()->SetPrev(nullptr);
			head = tmp->GetNext();
		}
		else {
			head = nullptr;
		}
	}
	else {
		//	Walk thru list
		while (tmp->GetNext() != nullptr && tmp->GetNext()->GetName() != name) {
			tmp = tmp->GetNext();
		}

		//	Check if name is in list
		if (tmp->GetNext() == nullptr) {
			return;
		}
		//	Continue looking for name
		else {
			//	Check if name is in middle
			//	update tmp to tmp = tmp->GetNext() - ?
			if (tmp->GetNext()->GetNext() != nullptr) {
				//	Mark for deletion
				orderToDelete = tmp->GetNext();
				tmp->SetNext(tmp->GetNext()->GetNext());
				tmp->GetNext()->SetPrev(tmp);
			}
			//	Name must be in tail
			else {
				//	Mark for deletion
				orderToDelete = tmp->GetNext();
				tmp->SetNext(nullptr);
			}
		}
	}

	/*
	//	Free hot dogs - apparently unnecessary since it's covered by destructor...
	//	Refactor above outer-else block...
	HotDog* hotDogsToDelete = orderToDelete->GetHead();
	while (hotDogsToDelete->GetNext() != nullptr) {
		hotDogsToDelete = hotDogsToDelete->GetNext();
		tmp->Remove(hotDogsToDelete->GetPrev());
	}
	orderToDelete->Remove(hotDogsToDelete);
	*/
	delete orderToDelete;
}

void Stand::Add(Order * const pOrder)
{
	Order* tmp = head;

	this->currentOrders++;
	if (this->currentOrders > peakOrders) {
		peakOrders++;
	}

	if (this->head == nullptr) {
		this->head = pOrder;
	}
	else {
		while (tmp->GetNext() != nullptr) {
			tmp = tmp->GetNext();
		}

		tmp->SetNext(pOrder);
		pOrder->SetPrev(tmp);
		pOrder->SetNext(nullptr);
	}
	//delete tmp;
}

//---  End of File ---

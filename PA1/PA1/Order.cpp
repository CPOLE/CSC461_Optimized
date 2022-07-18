//-----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#include "Order.h"
#include "Names.h"

// -----------------------------------------------
// AZUL_REPLACE_ME_STUB
// this is place holder for compiling purposes
// Delete each AZUL_REPLACE_ME_STUB line
// Replace with your own code
// -----------------------------------------------

// Methods
//	Big 4
Order::Order()
	: head(nullptr), prev(nullptr), next(nullptr)
{
	//
}

Order::Order(Name name)
	: head(nullptr), orderName(name), prev(nullptr), next(nullptr)
{
	//
}

Order::Order(const Order& o)
	: head(new HotDog(*o.head)), orderName(o.orderName), prev(nullptr), next(nullptr)
{
	HotDog* tmp = o.head;
	//	Copy linked list
	while (tmp->GetNext() != nullptr) {
		this->Add(new HotDog(*tmp->GetNext()));
		tmp = tmp->GetNext();
	}
}


Order& Order::operator = (const Order& o)
{
	this->head = new HotDog(*o.head);
	this->orderName = o.orderName;
	this->prev = nullptr;
	this->next = nullptr;

	HotDog* tmp = o.head;
	//	Copy linked list
	while (tmp->GetNext() != nullptr) {
		this->Add(new HotDog(*tmp->GetNext()));
		tmp = tmp->GetNext();
	}
	
	return *this;
}

Order::~Order()
{
	while (this->head != nullptr)
	{
		HotDog* tmp = this->head->GetNext();
		delete head;
		head = tmp;
	}
}

//
void Order::Add(HotDog *p)
{
	HotDog* tmp = head;

	if (head == nullptr) {
		this->head = p;
	}
	else {
		while (tmp->GetNext() != nullptr) {
			tmp = tmp->GetNext();
		}

		tmp->SetNext(p);
		p->SetPrev(tmp);
		p->SetNext(nullptr);
	}
}

void Order::Remove(HotDog* p)
{
	if (this->head == nullptr) {
		return;
	}
	//	Node is head
	if (this->head == p) {
		this->head = head->GetNext();
	}
	//	Node not at tail
	if (p->GetNext() != nullptr) {
		p->GetNext()->SetPrev(p->GetPrev());
	}
	//	Node not at head
	if (p->GetPrev() != nullptr) {
		p->GetPrev()->SetNext(p->GetNext());
	}
	delete p;
	return;
}

Order * const Order::GetNext() const
{
	return this->next;
}

Order * const Order::GetPrev() const
{
	return this->prev;
}

HotDog * const Order::GetHead() const
{
	return this->head;
}

void Order::SetNext(Order *p)
{
	this->next = p;
}

void Order::SetPrev(Order *p)
{
	this->prev = p;
}

Name Order::GetName() const
{
	return this->orderName;
}

void Order::SetName(const Name name)
{
	this->orderName = name;
}


//---  End of File ---

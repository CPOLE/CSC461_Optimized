//-----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#include "SearchList.h"
#include "Node.h"
#include "AList.h"

// --------------------------------
// -->    MODIFY This FILE    <----
// --------------------------------

void SearchList::MergeSort()
{
    // Initialize sorted linked list
    Node* sorted = this->pHead;
    sorted = mergeSort(sorted);
    this->pHead = sorted;
}

Node* SearchList::split(Node* head)
{
    Node* mid = head;
    Node* end = head;

    while (end->pNext && end->pNext->pNext) {
            end = end->pNext->pNext;
            mid = mid->pNext;
        }
    
    Node* right = mid->pNext;
    mid->pNext = nullptr;
    return right;
}

// Function to merge two linked lists
Node* SearchList::merge(Node* left, Node* right)
{
    // If first linked list is empty
    if (left == nullptr)
        return right;

    // If second linked list is empty
    if (right == nullptr)
        return left;

    // Pick the smaller value
    if (left->key < right->key)
    {
        left->pNext = merge(left->pNext, right);
        left->pNext->pPrev = left;
        left->pPrev = nullptr;
        return left;
    }
    else
    {
        right->pNext = merge(left, right->pNext);
        right->pNext->pPrev = right;
        right->pPrev = nullptr;
        return right;
    }
}

Node* SearchList::mergeSort(Node* head)
{
    if (head == nullptr || head->pNext == nullptr)
        return head;
    
    Node* right = split(head);

    head = mergeSort(head);
    right = mergeSort(right); 

    return merge(head, right);
}

void SearchList::InsertionSort()
{
    this->pHead = inSort(this->pHead);
}

Node* SearchList::inSort(Node* head)
{
    Node* sorted = nullptr;
    Node* current = head;
    while (current != nullptr)
    {
        // Store next for next iteration
        Node* next = current->pNext;
        current->pPrev = nullptr;
        current->pNext = nullptr;
        // Insert current in sorted linked list
        sortedInsert(&sorted, current);
        // Update current
        current = next;
    }
    return sorted;
}

void SearchList::sortedInsert(Node** sortedHead, Node* insertNode) 
{
    Node* current;
    /* Special case for the head end */
    if (*sortedHead == NULL) {
        *sortedHead = insertNode;
    }
    else if ((*sortedHead)->key >= insertNode->key) {
        insertNode->pNext = *sortedHead;
        insertNode->pNext->pPrev = insertNode;
        *sortedHead = insertNode;
    }
    else {
        /* Locate the node before the point of insertion */
        current = *sortedHead;
        while (current->pNext != nullptr && current->pNext->key < insertNode->key)
        {
            current = current->pNext;
        }
        if (current->pNext != nullptr)
            current->pNext->pPrev = insertNode;
        insertNode->pPrev = current;
        insertNode->pNext = current->pNext;
        current->pNext = insertNode;
    }
}

void SearchList::MergeComboSort(int CutoffLength)
{
    Node* sorted = this->pHead;
    int begin = 0;
    int end = this->GetNumNodes();
    this->pHead = mergeComboSort(sorted, begin, end, CutoffLength);
}

Node* SearchList::mergeComboSort(Node* head, int begin, int end, int cutoff)
{
    int subListSize = end - begin;

    if (subListSize < cutoff) {
        return inSort(head);
    }
    else {
        if (head == nullptr || head->pNext == nullptr)
            return head;

        int mid = (begin + end) / 2;
        Node* right = split(head);
        head = mergeComboSort(head, begin, mid, cutoff);
        right = mergeComboSort(right, mid, end, cutoff);
        return merge(head, right);
    }
}

// ---  End of File ---

#pragma once

#include "LinkedList.h"

template<class ElementType>
class StackLL : LinkedList<ElementType>
{
//typedef typename LinkedList<ElementType>::Node* LLNodePtr;
public:
	StackLL() : topPtr( NULL ) {}

	void operator = ( const StackLL& rhs );

	bool Push( const ElementType& element );
	bool Pop();
	bool Pop( ElementType& top_element );
	bool Top( ElementType& return_value ) const;
	bool IsFull() const;

	inline ElementType Top() const		{ return topPtr->element; }
	inline bool IsEmpty()	 const		{ return topPtr == NULL; }

private:
	Node* topPtr;
	LinkedList<ElementType> linkedList;
};






template<class ElementType>
void StackLL<ElementType>::operator = ( const StackLL& rhs )
{
	if( rhs.topPtr == NULL )
		topPtr = NULL;
	else
	{
		Node* ptr1;
		Node* ptr2;

		topPtr = new Node;
		topPtr->element = rhs.topPtr->element;
		ptr1 = rhs.topPtr->next;
		ptr2 = topPtr;

		while( ptr1 != NULL )
		{
			ptr2->next = new Node;
			ptr2 = ptr2->next;
			ptr2->element = ptr1->element;
			ptr1 = ptr1->next;
		}
		ptr2->next = NULL;
	}
}

template<class ElementType>
bool StackLL<ElementType>::Push( const ElementType& element )
{
	bool successful = false;

	if( !IsFull() )
	{
		linkedList.Insert( element, true );
		topPtr = linkedList.First();
		successful = true;
	}
	return successful;
}

template<class ElementType>
bool StackLL<ElementType>::Pop()
{
	bool successful = false;

	if( !IsEmpty() )
	{
		linkedList.Delete( topPtr->element );
		topPtr = linkedList.First();
		successful = true;
	}
	return successful;
}

template<class ElementType>
bool StackLL<ElementType>::Pop( ElementType& top_element )
{
	bool successful = false;

	if( !IsEmpty() )
	{
		top_element = topPtr->element;
		linkedList.Delete( topPtr->element );
		topPtr = linkedList.First();
		successful = true;
	}
	return successful;
}

template<class ElementType>
bool StackLL<ElementType>::Top( ElementType& return_value ) const
{
	bool successful = false;

	if( !IsEmpty() )
	{
		return_value = topPtr->element;
		successful = true;
	}

	return successful;
}

template<class ElementType>
bool StackLL<ElementType>::IsFull() const
{
	Node* tempPtr;
	try
	{
		tempPtr = new Node;
		delete tempPtr;
		return false;
	}
	catch( std::bad_alloc exception ) { return true; }
}
#pragma once

#include "LinkedList.h"

template<class ElementType>
class QueueLL : LinkedList<ElementType>
{
public:
	QueueLL() : frontPtr( NULL ), backPtr( NULL ) {}

	bool Enqueue( const ElementType& back_element );
	bool Dequeue( ElementType& front_element );
	void Flush();

	inline ElementType Front() const	{ return frontPtr->element; }
	inline bool IsEmpty() const			{ return frontPtr == NULL; }

	bool IsFull() const;


private:
	Node* frontPtr;
	Node* backPtr;
	LinkedList<ElementType> linkedList;
};




template<class ElementType>
bool QueueLL<ElementType>::Enqueue( const ElementType& back_element )
{
	bool successful;

	if( !IsFull() )
	{
		linkedList.Insert( back_element );

		if( backPtr == NULL )
			frontPtr = linkedList.First();

		backPtr = linkedList.Last();

		successful = true;
	}

	return successful;
}

template<class ElementType>
bool QueueLL<ElementType>::Dequeue( ElementType& front_element )
{
	bool successful = false;

	if( !IsEmpty() )
	{
		front_element = frontPtr->element;
		linkedList.Delete( frontPtr->element );
		frontPtr = linkedList.First();

		if( frontPtr == NULL )
			backPtr = NULL;

		successful = true;
	}

	return successful;
}

template<class ElementType>
void QueueLL<ElementType>::Flush()
{
	Node* current;

	while( !IsEmpty() )
	{
		current = frontPtr;
		frontPtr = frontPtr->next;
		linkedList.Delete( linkedList.First()->element );
	}
	backPtr = NULL;
}

template<class ElementType>
bool QueueLL<ElementType>::IsFull() const
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
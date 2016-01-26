#pragma once

#ifndef NULL
#define NULL 0
#endif

template<class ElementType, bool ordered = false>
class CircularDoublyLL
{
public:
	struct Node
	{
		ElementType element;
		Node* next;
		Node* prior;

		Node( ElementType e ) : element( e ), next( NULL ), prior( NULL ) {}
	};

	//**** Constructors ****//
	CircularDoublyLL() : last( NULL ), num_elements( 0 ) {}
	~CircularDoublyLL();

	//**** Operators ****//
	bool operator == ( CircularDoublyLL& rhs ) const;

	//**** Modifiers ****//
	void Append( CircularDoublyLL< ElementType >& other );
	void Insert( ElementType element, bool at_beginning = true );
	void Delete( ElementType element );

	//**** Searching ****//
	bool Find( const ElementType element, Node*& targetNode ) const;
	ElementType Find( const ElementType& element ) const;

	//**** Observers ****//
	Node* First()	const	{ return last->next; }
	Node* Last()	const	{ return last; }
	bool  IsEmpty()	const	{ return last == NULL; }


	class Iterator
	{
	private:
		Node* current;

	public:
		Iterator() : current( NULL ) {}

		Iterator( Node* node ) : current( node ) {}

		ElementType& operator * ()
		{
			return current->element;
		}

		Node* operator ++ ()
		{
			if( current )
				current = current->next;
			return current;
		}

		bool operator != ( Node* ptr )
		{
			return current != ptr;
		}

		void operator = ( Node* ptr )
		{
			current = ptr;
		}
	};


private:
		Node* last;
		int num_elements;
};






template<class ElementType, bool ordered = false>
CircularDoublyLL<ElementType, ordered>::~CircularDoublyLL()
{
	Node* current;

	while( last != NULL )
	{
		current = last;
		last = last->prior;
		delete current;
		current = NULL;
	}
	num_elements = 0;
}


//**** Operators ****//
template<class ElementType, bool ordered = false>
bool CircularDoublyLL<ElementType, ordered>::operator == ( CircularDoublyLL& rhs ) const
{
	Node* thisCurrent = First();
	Node* otherCurrent = rhs.First();

	bool equal;

	if( num_elements == rhs.num_elements )
		for( thisCurrent; thisCurrent != last; thisCurrent = thisCurrent->next, otherCurrent = otherCurrent->next )
			equal &= thisCurrent == otherCurrent;
	else
		equal = false;

	return equal;
}


//**** Modifiers ****//
template<class ElementType, bool ordered = false>
void CircularDoublyLL<ElementType, ordered>::Append( CircularDoublyLL<ElementType>& other )
{
	Node* L1 = last;
	Node* L2 = other.last;

	if( !IsEmpty() )
	{
		Node* L1_next = L1->next;
		Node* L2_next = L2->next;

		L1_next->prior = L2;
		L2_next->prior = L1;

		L1->next = L2_next;
		L2->next = L1_next;
	}
	last = L2;
	num_elements += other.num_elements;
	other.last = NULL;
	other.num_elements = 0;
}

template<class ElementType, bool ordered = false>
void CircularDoublyLL<ElementType, ordered>::Insert( ElementType element, bool at_beginning = true )
{
	Node* newNode = new Node( element );

	if( IsEmpty() )
	{
		newNode->prior = newNode;
		newNode->next = newNode;
		last = newNode;
	}
	else
	{
		if( ordered == true )
		{
			Node* currentPtr = First();

			if( element > currentPtr->element )
				do {
					currentPtr = currentPtr->next;
				} while( currentPtr != First() && element > currentPtr->element );

				newNode->prior = currentPtr->prior;
				newNode->next = currentPtr;
				currentPtr->prior->next = newNode;
				currentPtr->prior = newNode;

				if( newNode->element > last->element )
					last = newNode;
		}
		else // if not ordered
		{
			newNode->prior = last;
			newNode->next = last->next;
			last->next->prior = newNode;
			last->next = newNode;

			if( !at_beginning )		// at the end
				last = last->next;
		}
	}
	num_elements++;
}

template<class ElementType, bool ordered = false>
void CircularDoublyLL<ElementType, ordered>::Delete( ElementType element )
{
	Node* targetNode = NULL;
	bool found = Find( element, targetNode );

	if( found )
	{
		Node* temp = targetNode;

		if( targetNode == last )
			last = targetNode->prior;

		targetNode->prior->next = targetNode->next;
		targetNode->next->prior = targetNode->prior;

		delete temp;
		--num_elements;
	}
}


//**** Searching ****//
template<class ElementType, bool ordered = false>
bool CircularDoublyLL<ElementType, ordered>::Find( const ElementType element, Node*& targetNode ) const
{
	Node* current = First();
	bool found = true;

	if( IsEmpty() )
		found = false;
	else if( element != current->element )
	{
		current = current->next;
		while( current != First() && element != current->element )
			current = current->next;

		if( current == First() )
			found = false;
		else
			targetNode = current;
	}
	return found;
}

template<class ElementType, bool ordered = false>
ElementType CircularDoublyLL<ElementType, ordered>::Find( const ElementType& element ) const
{
	Node* current = First();

	while( current != First() && current->element != element )
		current = current->next;

	return current->element;
}
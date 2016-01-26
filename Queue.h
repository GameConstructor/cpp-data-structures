#pragma once

template<class ElementType, int size = 64>
class Queue
{
public:
	Queue() : front( 0 ), back( 0 ) {}

	bool Enqueue( const ElementType& back_element );
	bool Dequeue( ElementType& front_element );
	void Flush();

	inline ElementType Front()	{ return queueArray[front]; }
	inline bool IsEmpty()		{ return back == front; }
	inline bool IsFull()		{ return front == ( back + 1 ) % size; }


private:
	int front, back;
	ElementType queueArray[size];
};




template<class ElementType, int size = 64>
bool Queue<ElementType, size>::Enqueue( const ElementType& back_element )
{
	bool successful;

	if( !IsFull() )
	{
		queueArray[back++] = back_element;
		back %= size;
		successful = true;
	}
	else
		successful = false;

	return successful;
}

template<class ElementType, int size = 64>
bool Queue<ElementType, size>::Dequeue( ElementType& front_element )
{
	bool successful;

	if( !IsEmpty() )
	{
		front_element = queueArray[front];
		queueArray[front++] = 0xcccccccc;
		front %= size;
		successful = true;
	}
	else
		successful = false;

	return successful;
}

template<class ElementType, int size = 64>
void Queue<ElementType, size>::Flush()
{
	while( !IsEmpty() )
	{
		queueArray[front++] = 0xcccccccc;
		front %= size;
	}
}
#pragma once

#include "MaxHeap.h"

template<class ElementType>
class PriorityQueue
{
public:
    PriorityQueue() { }

    void Enqueue( ElementType element );
    void Dequeue( ElementType& element );
    void Peek( ElementType& element ) const;

    inline int  Size()	  const		{ return maxHeap.Size(); }
    inline bool IsEmpty() const		{ return maxHeap.Size() == 0; }


private:
    MaxHeap<ElementType> maxHeap;
};




template<class ElementType>
void PriorityQueue<ElementType>::Enqueue( ElementType element )
{
    maxHeap.Append( element );
}

template<class ElementType>
void PriorityQueue<ElementType>::Dequeue( ElementType& element )
{
    element = maxHeap.RemoveNext();
}

template<class ElementType>
void PriorityQueue<ElementType>::Peek( ElementType& element ) const
{
    element = maxHeap.Peek();
}
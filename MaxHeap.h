#pragma once

#include <algorithm>

template<class ElementType>
class MaxHeap
{
public:
    static void Sort( ElementType* elements, int size );
    MaxHeap();
    MaxHeap( ElementType* elements, int size );
    ElementType RemoveNext();
    void Append( ElementType element );

    inline int         Size() const	{ return size; }
    inline ElementType Peek() const	{ return size > 0 ? elements[0] : NULL; }

private:
    inline int LeftChildIdx( int parentIdx )  const	{ return parentIdx * 2 + 1; }
    inline int RightChildIdx( int parentIdx ) const	{ return parentIdx * 2 + 2; }
    inline int ParentIdx( int childIdx )	  const	{ return ( childIdx - 1 ) >> 1; }

    void HeapUp( int childIdx );                    // used to restore heap after appending a new element
    void Heapify( int parentIdx );                  // used for normal (top-down) implementation of heap sort
    void BottomUpHeapify( int lastIdx );            // used for bottom-up implementation of heap sort
    int GetMaxLeafIdx( int rootIdx, int lastIdx );  // used for bottom-up implementation of heap sort

    const int defaultCapacity = 64;
    ElementType* elements;
    int size;
};






template<class ElementType>
void MaxHeap<ElementType>::Sort( ElementType* elements, int size )
{
    MaxHeap heap = MaxHeap( elements, size );
    for( int i = heap.Size() - 1; i >= 0; --i )
    {
        ElementType nextMax = heap.RemoveNext();
        heap.elements[i] = nextMax;
    }
}


template<class ElementType>
MaxHeap<ElementType>::MaxHeap()
{
    elements = new ElementType[defaultCapacity];
    size = 0;
}


template<class ElementType>
MaxHeap<ElementType>::MaxHeap( ElementType* elements, int size )
{
    this->elements = elements;
    this->size = size;
    int idxOfLastParent = ParentIdx( size - 1 );
    for( int i = idxOfLastParent; i >= 0; --i )
        Heapify( i );
}


template<class ElementType>
void MaxHeap<ElementType>::Append( ElementType element )
{
    if( size < defaultCapacity )
    {
        elements[size] = element;
        HeapUp( size );
        ++size;
    }
}


template<class ElementType>
ElementType MaxHeap<ElementType>::RemoveNext()
{
    if( size > 0 )
    {
        ElementType max = elements[0];
        elements[0] = elements[--size];
        elements[size] = NULL;
        Heapify( 0 );                       // uncomment this line for top-down merge sort
        //BottomUpHeapify( size - 1 );      // OR uncomment this line for bottom-up merge sort
        return max;
    }
    else
        return NULL;
}


template<class ElementType>
void MaxHeap<ElementType>::HeapUp( int childIdx )
{
    if( childIdx > 0 )
    {
        int parentIdx = ParentIdx( childIdx );
        if( elements[parentIdx] < elements[childIdx] )
        {
            std::swap( elements[parentIdx], elements[childIdx] );
            HeapUp( parentIdx );
        }
    }
}


template<class ElementType>
void MaxHeap<ElementType>::Heapify( int parentIdx )
{
    int maxChildIdx;
    int leftChildIdx = LeftChildIdx( parentIdx );

    if( leftChildIdx < size )
    {
        maxChildIdx = leftChildIdx;
        int rightChildIdx = RightChildIdx( parentIdx );

        if( rightChildIdx < size && elements[rightChildIdx] > elements[leftChildIdx] )
            maxChildIdx = rightChildIdx;

        if( elements[parentIdx] < elements[maxChildIdx] )
        {
            std::swap( elements[parentIdx], elements[maxChildIdx] );
            Heapify( maxChildIdx );
        }
    }
}


template<class ElementType>
void MaxHeap<ElementType>::BottomUpHeapify( int lastIdx )
{
    int maxLeafIdx = GetMaxLeafIdx( 0, lastIdx );
    while( elements[0] > elements[maxLeafIdx] )
        maxLeafIdx = ParentIdx( maxLeafIdx );

    ElementType temp = elements[maxLeafIdx];
    elements[maxLeafIdx] = elements[0];
    while( maxLeafIdx > 0 )
    {
        maxLeafIdx = ParentIdx( maxLeafIdx );
        std::swap( temp, elements[maxLeafIdx] );
    }
}


template<class ElementType>
int MaxHeap<ElementType>::GetMaxLeafIdx( int rootIdx, int lastIdx )
{
    int maxLeaf = rootIdx;
    int leftChildIdx = LeftChildIdx( maxLeaf );
    while( leftChildIdx <= lastIdx )
    {
        int rightChildIdx = leftChildIdx + 1;
        if( rightChildIdx <= lastIdx && elements[rightChildIdx] > elements[leftChildIdx] )
            maxLeaf = rightChildIdx;
        else
            maxLeaf = leftChildIdx;
        leftChildIdx = LeftChildIdx( maxLeaf );
    }

    return maxLeaf;
}
#pragma once

#include "assert.h"

template<typename T, size_t N>
inline size_t arraySize( const T(&)[N] ) { return N; }

template<class ElementType, bool ordered = false>
class DynamicArray
{
public:
    //****Constructors ****//
    DynamicArray();
    DynamicArray( int size );
    ~DynamicArray();

    //**** Operators ****//
    void		 operator =  ( const DynamicArray& rhs );
    bool		 operator == ( const DynamicArray& other ) const;
    ElementType& operator [] ( int index );

    //**** Modifiers ****//
    void ExpandArray();
    void Append( ElementType element );
    void Insert( ElementType element );
    void Delete( int index );
    void Swap( int idx1, int idx2 );

    //**** Search ****//
    int Find( const ElementType& key ) const;
    int LinearSearch( const ElementType& key ) const;
    int BinarySearch( const ElementType& key ) const;

    //**** Sorting ****//
    void SelectionSort();
    void BubbleSort();
    void InsertionSort();
    void QuickSort();
    void MergeSort();

    //**** Observers ****//
    inline int GetLength() const	{ return num_elements; }


private:
    int size;
    int num_elements;
    ElementType* array;

    //**** Sorting Helpers ****//
    void SelectionSort( ElementType* arr, int n );
    void BubbleSort( ElementType* arr, int n );
    void InsertionSort( ElementType* arr, int n );
    void QuickSort( ElementType* arr, int startIdx, int endIdx );
    int Partition( ElementType* arr, int startIdx, int endIdx );
    void MergeSort( ElementType* arr, int n );
    void Merge( ElementType* parent, ElementType* left,  int leftSize,
                                     ElementType* right, int rightSize );
};






//****Constructors ****//
template<class ElementType, bool ordered = false>
DynamicArray<ElementType, ordered>::DynamicArray()
{
    size = 100;
    num_elements = 0;
    array = new ElementType[size];
}

template<class ElementType, bool ordered = false>
DynamicArray<ElementType, ordered>::DynamicArray( int size )
{
    assert( size > 0 );
    this->size = size;
    num_elements = 0;
    array = new ElementType[size];
}

template<class ElementType, bool ordered = false>
DynamicArray<ElementType, ordered>::~DynamicArray()
{
    delete [] array;
    array = NULL;
    size = num_elements = 0;
}


//**** Operators ****//
template<class ElementType, bool ordered = false>
void DynamicArray<ElementType, ordered>::operator = ( const DynamicArray& rhs )
{
    if( size == rhs.size )
        for( int i = 0; i < size; i++ )
            array[i] = rhs.array[i];
    else
    {
        delete [] array;
        array = NULL;

        array = new ElementType[rhs.size];
        for( int i = 0; i < rhs.num_elements; i++ )
            array[i] = rhs.array[i];

        size = rhs.size;
    }
    num_elements = rhs.num_elements;
}

template<class ElementType, bool ordered = false>
bool DynamicArray<ElementType, ordered>::operator == ( const DynamicArray& other ) const
{
    bool result = true;

    if( (size == other.size) && (num_elements == other.num_elements) )
        for( int i = 0; i < size; i++ )
            result &= array[i] == other.array[i];
    else
        result = false;

    return result;
}

template<class ElementType, bool ordered = false>
ElementType& DynamicArray<ElementType, ordered>::operator [] ( int index )
{
    assert( index >= 0 && index < size );

    return array[index];
}


//**** Modifiers ****//
template<class ElementType, bool ordered = false>
void DynamicArray<ElementType, ordered>::ExpandArray()
{
    size = size << 1;
    ElementType* temp = new ElementType[size];

    for( int i = 0; i < num_elements; i++ )
        temp[i] = array[i];

    delete [] array;
    array = temp;
}

template<class ElementType, bool ordered = false>
void DynamicArray<ElementType, ordered>::Append( ElementType element )
{
    if( num_elements == size ) ExpandArray();
    array[num_elements++] = element;
}

template<class ElementType, bool ordered = false>
void DynamicArray<ElementType, ordered>::Insert( ElementType element )
{
    if( num_elements == size ) ExpandArray();

    if( ordered )
    {
        int currentSlot = 0;

        while( currentSlot < num_elements && element > array[currentSlot] )
            currentSlot++;
            
        for( int i = num_elements; i > currentSlot; i-- )
            array[i] = array[i - 1];

        array[currentSlot] = element;
        num_elements++;
    }
    else
        Append( element );
}

template<class ElementType, bool ordered = false>
void DynamicArray<ElementType, ordered>::Delete( int index )
{
    for( index; index < num_elements - 1; index++ )
        array[index] = array[index + 1];

    array[--num_elements] = NULL;
}

template<class ElementType, bool ordered = false>
void DynamicArray<ElementType, ordered>::Swap( int idx1, int idx2 )
{
    assert( (idx1 >=0 && idx1 < num_elements) && (idx2 >=0 && idx2 < num_elements) );
    ElementType temp = array[idx1];
    array[idx1] = array[idx2];
    array[idx2] = temp;
}


//**** Search ****//
template<class ElementType, bool ordered = false>
int DynamicArray<ElementType, ordered>::Find( const ElementType& key ) const
{
    return ordered ? BinarySearch( key ) : LinearSearch( key );
}

template<class ElementType, bool ordered = false>
int DynamicArray<ElementType, ordered>::LinearSearch( const ElementType& key ) const
{
    bool found = false;
    int keySlot = -1;
    int current = 0;

    while( !found && current < num_elements )
        if( key == array[current] )
        {
            keySlot = current;
            found = true;
        }
        else
            current++;

    return keySlot;
}

template<class ElementType, bool ordered = false>
int DynamicArray<ElementType, ordered>::BinarySearch( const ElementType& key ) const
{
    int keySlot = -1;
    int low, mid, high;
    bool found = false;
    low = 0;
    high = num_elements - 1;

    while( !found && low <= high )
    {
        mid = low + ( high - low ) >> 1;
        if( key == array[mid] )
        {
            keySlot = mid;
            found = true;
        }
        else if( key < array[mid] )
            high = mid - 1;
        else
            low = mid + 1;
    }

    return keySlot;
}


//**** Sorting ****//
template<class ElementType, bool ordered = false>
void DynamicArray<ElementType, ordered>::SelectionSort()
{
    SelectionSort( array, num_elements );
}

template<class ElementType, bool ordered = false>
void DynamicArray<ElementType, ordered>::SelectionSort( ElementType* arr, int n )
{
    for( int slot = 0; slot < n - 1; ++slot )
    {
        int minIdx = slot;
        for( int testIdx = slot + 1; testIdx < n; ++testIdx )
        {
            if( arr[testIdx] < arr[minIdx] )
                minIdx = testIdx;
        }
        if( minIdx != slot )
            Swap( slot, minIdx );
    }
}

template<class ElementType, bool ordered = false>
void DynamicArray<ElementType, ordered>::BubbleSort()
{
    BubbleSort( array, num_elements );
}

template<class ElementType, bool ordered = false>
void DynamicArray<ElementType, ordered>::BubbleSort( ElementType* arr, int n )
{
    for( int pass = 1; pass < n; ++pass )
    {
        bool didSwap = false;
        for( int i = 0; i < n - pass; ++i )
        {
            if( arr[i] > arr[i + 1] )
            {
                Swap( i, i + 1 );
                didSwap = true;
            }
        }
        if( !didSwap )
            break;
    }
}

template<class ElementType, bool ordered = false>
void DynamicArray<ElementType, ordered>::InsertionSort()
{
    InsertionSort( array, num_elements );
}

template<class ElementType, bool ordered = false>
void DynamicArray<ElementType, ordered>::InsertionSort( ElementType* arr, int n )
{
    for( int pass = 1; pass < n; ++pass )
    {
        int slot = pass;
        int val = arr[slot];
        while( slot > 0 && val < arr[slot - 1] )
        {
            arr[slot] = arr[slot - 1];
            --slot;
        }
        arr[slot] = val;
    }
}

template<class ElementType, bool ordered = false>
void DynamicArray<ElementType, ordered>::QuickSort()
{
    QuickSort( array, 0, num_elements - 1 );
}

template<class ElementType, bool ordered = false>
void DynamicArray<ElementType, ordered>::QuickSort( ElementType* arr, int startIdx, int endIdx )
{
    if( startIdx >= endIdx )
        return;

    int partitionIdx = Partition( arr, startIdx, endIdx );
    QuickSort( arr, startIdx, partitionIdx - 1 );
    QuickSort( arr, partitionIdx + 1, endIdx );
}

template<class ElementType, bool ordered = false>
int DynamicArray<ElementType, ordered>::Partition( ElementType* arr, int startIdx, int endIdx )
{
    int pivotIdx = endIdx;
    int currentIdx = startIdx;
    for( int i = startIdx; i < endIdx; ++i )
    {
        if( arr[i] < arr[pivotIdx] )
        {
            Swap( i, currentIdx );
            ++currentIdx;
        }
    }
    Swap( currentIdx, pivotIdx );

    return currentIdx;
}

template<class ElementType, bool ordered = false>
void DynamicArray<ElementType, ordered>::MergeSort()
{
    MergeSort( array, num_elements );
}

template<class ElementType, bool ordered = false>
void DynamicArray<ElementType, ordered>::MergeSort( ElementType* arr, int n )
{
    if( n < 2 )
        return;

    int leftSize = n / 2;
    int rightSize = n - leftSize;

    int* left = new int[leftSize];
    int* right = new int[rightSize];

    for( int i = 0; i < leftSize; ++i )
        left[i] = arr[i];
    for( int i = 0; i < rightSize; ++i )
        right[i] = arr[i + leftSize];

    MergeSort( left, leftSize );
    MergeSort( right, rightSize );
    Merge( arr, left, leftSize, right, rightSize );

    delete[] left;
    delete[] right;
}

template<class ElementType, bool ordered = false>
void DynamicArray<ElementType, ordered>::Merge( ElementType* parent, ElementType* left,  int leftSize,
                                                                     ElementType* right, int rightSize )
{
    int parentIdx = 0, leftIdx = 0, rightIdx = 0;

    while( leftIdx < leftSize && rightIdx < rightSize )
    {
        if( left[leftIdx] <= right[rightIdx] )
            parent[parentIdx++] = left[leftIdx++];
        else
            parent[parentIdx++] = right[rightIdx++];
    }

    while( leftIdx < leftSize )
        parent[parentIdx++] = left[leftIdx++];
    while( rightIdx < rightSize )
        parent[parentIdx++] = right[rightIdx++];
}
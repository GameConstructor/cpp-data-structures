#pragma once

#define NodePtr typename LinkedList<ElementType, ordered>::Node*

template<class ElementType, bool ordered = false>
class LinkedList
{
public:
    struct Node
    {
        ElementType element;
        Node* next;

        Node() : next( NULL ) {}
        Node( ElementType e ) : element( e ), next( NULL ) {}
    };

    LinkedList() : first( NULL ), last( NULL ), num_elements( 0 ) {}
    ~LinkedList();

    void Insert( const ElementType& element, bool at_beginning = false );
    void Append( LinkedList<ElementType, ordered>& other );
    void Delete( ElementType element );

    //**** Searching ****//
    // stores the prior node of the one that contains the element
    bool Find( const ElementType element, Node*& priorNode ) const;

    //**** Sorting ****//
    Node* MergeSort();

    //**** Observers ****//
    inline Node* First()   const	{ return first; }
    inline Node* Last()	   const	{ return last; }
    inline bool  IsEmpty() const	{ return first == NULL; }
    inline int   Length()  const	{ return num_elements; }

    class Iterator
    {
    private:
        Node* current;

    public:
        Iterator() : current( NULL ) {}
        Iterator( Node* node ) : current( node ) {}

        ElementType& operator * ( )
        {
            return current->element;
        }

        Node* operator ++ ( )
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
    Node* first;
    Node* last;
    int num_elements;

    Node* MergeSort( Node* list, int n );
};






template<class ElementType, bool ordered = false>
LinkedList<ElementType, ordered>::~LinkedList()
{
    Node* current;

    while( first != NULL )
    {
        current = first;
        first = first->next;
        delete current;
        current = NULL;
    }
    num_elements = 0;
}

template<class ElementType, bool ordered = false>
void LinkedList<ElementType, ordered>::Insert( const ElementType& element, bool at_beginning = false )
{
    Node* newNode = new Node( element );

    if( IsEmpty() )
        first = last = newNode;
    else
    {
        if( ordered == true )
        {
            Node* currentPtr = first;
            Node* trailingPtr = NULL;

            while( currentPtr != NULL && element > currentPtr->element )
            {
                trailingPtr = currentPtr;
                currentPtr = currentPtr->next;
            }

            newNode->next = currentPtr;
            if( trailingPtr != NULL )
                trailingPtr->next = newNode;
            else
                first = newNode;
            if( newNode->element > last->element )
                last = newNode;
        }
        else // if not ordered
        {
            if( at_beginning )
            {
                newNode->next = first;
                first = newNode;
            }
            else // at the end
            {
                last->next = newNode;
                last = newNode;
            }
        }
    }
    num_elements++;
}

template<class ElementType, bool ordered = false>
void LinkedList<ElementType, ordered>::Append( LinkedList<ElementType, ordered>& other )
{
    Node* current = first;

    if( IsEmpty() )
        first = other.first;
    else
    {
        while( current->next != NULL )
            current = current->next;

        current->next = other.first;
    }

    num_elements += other.num_elements;
    last = other.last;
    other.first = other.last = NULL;
    other.num_elements = 0;
}

template<class ElementType, bool ordered = false>
void LinkedList<ElementType, ordered>::Delete( ElementType element )
{
    Node* priorNode = NULL;
    bool found = Find( element, priorNode );

    if( found )
    {
        Node* targetNode = ( priorNode == NULL ? first : priorNode->next );
        Node* temp = targetNode;
        if( targetNode == first )
            first = targetNode->next;
        else
        {
            if( targetNode == last )
                last = priorNode;

            priorNode->next = targetNode->next;
        }
        delete temp;
        --num_elements;

        if( IsEmpty() )
            last = NULL;
    }
}


//**** Searching ****//
template<class ElementType, bool ordered = false>
bool LinkedList<ElementType, ordered>::Find( const ElementType element, Node*& priorNode ) const
{
    Node* current = first;
    bool found = true;

    if( IsEmpty() )
        found = false;
    else if( element != current->element )
    {
        while( current->next != NULL && element != ( current->next )->element )
            current = current->next;

        if( current->next == NULL )
            found = false;
        else
            priorNode = current;
    }
    return found;
}


//**** Sorting ****//
template<class ElementType, bool ordered = false>
NodePtr LinkedList<ElementType, ordered>::MergeSort()
{
    return MergeSort( first, num_elements );
}

template<class ElementType, bool ordered = false>
NodePtr LinkedList<ElementType, ordered>::MergeSort( Node* list, int n )
{
    //********** Dividing**********//
    if( n <= 1 ) return list;

    int mid = n / 2;

    Node* current = list;
    for( int i = 1; i < mid; i++ )
        current = current->next;

    Node* left = list;
    Node* right = current->next;
    list = current->next = NULL;

    left = MergeSort( left, mid );
    right = MergeSort( right, n - mid );

    //********** Merging**********//
    list = current = NULL;

    while( left != NULL && right != NULL )
    {
        if( left->element < right->element )
        {
            if( list == NULL )
            {
                list = current = left;
                first = current;
                left = left->next;
            }
            else
            {
                current->next = left;
                left = left->next;
                current = current->next;
            }
        }
        else
        {
            if( list == NULL )
            {
                list = current = right;
                first = current;
                right = right->next;
            }
            else
            {
                current->next = right;
                right = right->next;
                current = current->next;
            }
        }
    }
    while( left != NULL )
    {
        current->next = left;
        left = left->next;
        current = current->next;
        last = current;
    }
    while( right != NULL )
    {
        current->next = right;
        right = right->next;
        current = current->next;
        last = current;
    }
    return list;
}
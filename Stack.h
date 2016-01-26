#pragma once

template<class ElementType, int size = 64>
class Stack
{
public:
    Stack() : top( -1 ) {}

    bool Push( const ElementType& element );
    bool Pop();
    bool Pop( ElementType& top_element );
    bool Top( ElementType& return_value );

    inline ElementType Top()	{ return stackArray[top]; }
    inline bool IsEmpty()		{ return top == -1; }
    inline bool IsFull()		{ return top == size - 1; }

private:
    int top;
    ElementType stackArray[size];
};






template<class ElementType, int size = 64>
bool Stack<ElementType, size>::Push( const ElementType& element )
{
    bool successful = false;

    if( !IsFull() )
    {
        stackArray[++top] = element;
        successful = true;
    }

    return successful;
}

template<class ElementType, int size = 64>
bool Stack<ElementType, size>::Pop()
{
    bool successful = false;

    if( top >= 0 )
    {
        stackArray[top--] = NULL;
        successful = true;
    }

    return successful;
}

template<class ElementType, int size = 64>
bool Stack<ElementType, size>::Pop( ElementType& top_element )
{
    bool successful = false;

    if( top >= 0 )
    {
        top_element = stackArray[top];
        stackArray[top--] = NULL;
        successful = true;
    }

    return successful;
}

template<class ElementType, int size = 64>
bool Stack<ElementType, size>::Top( ElementType& return_value )
{
    bool successful = false;

    if( !IsEmpty() )
    {
        return_value = stackArray[top];
        successful = true;
    }

    return successful;
}
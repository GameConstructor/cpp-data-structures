#pragma once

#include<algorithm>
#include<iostream>
#include<queue>
#include <math.h>

template<class ElementType>
class BinaryTree
{
public:
	struct TreeNode
	{
		ElementType element;
		TreeNode* left;
		TreeNode* right;
		int nodes;

		TreeNode( ElementType e ) : element( e ), left( NULL ), right( NULL ), nodes( 0 ) {}

		TreeNode* Copy()
		{
			TreeNode* copy;

			if( this == NULL )
				copy = NULL;
			else
			{
				copy = new TreeNode( this->element );
				copy->nodes = nodes;
				copy->left  = left->Copy();
				copy->right = right->Copy();
			}
			return copy;
		}

		TreeNode* Delete()
		{
			if( this != NULL )
			{
				left->Delete();
				right->Delete();
				delete this;
			}
			return NULL;
		}

		bool Equal( TreeNode* rhs )
		{
			if( this == NULL && rhs == NULL ) return true;

			if( this->element == rhs->element )
				if( this->left->Equal( rhs->left ) )
					return this->right->Equal( rhs->right );
			return false;
		}
	};

	//**** Constructors ****//
	BinaryTree() : root( NULL ) {}
	BinaryTree( const BinaryTree& original );

	//**** Operators ****//
	void operator = ( const BinaryTree& other );
	bool operator == ( const BinaryTree& rhs ) const;

	//**** Queries ****//
	int  NodeCount() const;
	bool IsBst() const;

	//**** Observers ****//
	inline bool IsEmpty() const	{ root == NULL; }


protected:
	TreeNode* root;


private:
	int NodeCount_Recursive( TreeNode* tree ) const;
	bool IsBst( TreeNode* tree, int min, int max ) const;
};






template<class ElementType>
BinaryTree<ElementType>::BinaryTree( const BinaryTree& original )
{
	root = original.root->Copy();
}

//**** Operators ****//
template<class ElementType>
void BinaryTree<ElementType>::operator = ( const BinaryTree& other )
{
	if( &other == this ) return;

	root->Delete();
	root = other.root->Copy();
}

template<class ElementType>
bool BinaryTree<ElementType>::operator == ( const BinaryTree& rhs ) const
{
	if( root->nodes == rhs.root->nodes )
		return root->Equal( rhs.root );
	else
		return false;
}

//**** Queries ****//
template<class ElementType>
int BinaryTree<ElementType>::NodeCount() const
{
	return NodeCount_Recursive( root );
}

template<class ElementType>
int BinaryTree<ElementType>::NodeCount_Recursive( TreeNode* tree ) const
{
	if( tree == NULL )
		return 0;
	else
		return NodeCount_Recursive( tree->left ) + NodeCount_Recursive( tree->right ) + 1;
}

template<class ElementType>
bool BinaryTree<ElementType>::IsBst() const
{
	return IsBst( root, -(int)std::numeric_limits<int>::max, (int)std::numeric_limits<int>::max );
}

template<class ElementType>
bool BinaryTree<ElementType>::IsBst( TreeNode* tree, int min, int max ) const
{
	if( tree == NULL )
		return true;

	if( tree->element > min && tree->element < max &&
		IsBst( tree->left, min, tree->element ) &&
		IsBst( tree->right, tree->element, max ) )
		return true;
	else
		return false;
}
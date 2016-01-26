#pragma once

#define TreeNodePtr typename BinaryTree<ElementType>::TreeNode*

template<class ElementType>
class BinarySearchTree : public BinaryTree<ElementType>
{
public:
    //**** Modifiers ****//
    void Insert( const ElementType& element );
    void Remove( const ElementType& element );

    //**** Searching ****//
    void DFS() const;
    void BFS() const;
    bool Find( const ElementType& element ) const;
    TreeNode* GetInOrderSuccessor( const ElementType& element ) const;
    TreeNode* GetInOrderPredecessor( const ElementType& element ) const;

    //**** Observers ****//
    int GetHeight() const;


private:
    bool Find_Recursive( const ElementType& element, TreeNode* tree ) const;

    TreeNode* GetNode_Recursive( const ElementType& element, TreeNode* tree ) const;

    void Insert_Recursive( ElementType element, TreeNode*& tree );
    TreeNode* Remove( TreeNode* tree, ElementType element );

    //**** Searching ****//
    TreeNode* FindMin( TreeNode* tree ) const;
    TreeNode* FindMin_Recursive( TreeNode* tree ) const;
    TreeNode* FindMax( TreeNode* tree ) const;
    TreeNode* FindMax_Recursive( TreeNode* tree ) const;

    void BFS_( TreeNode* tree ) const;

    //**** DFS Traversal Options ****//
    void PreOrder( TreeNode* tree ) const;
    void InOrder( TreeNode* tree ) const;
    void PostOrder( TreeNode* tree ) const;

    //**** Observers ****//
    int GetHeight( TreeNode* tree ) const;
};





template<class ElementType>
bool BinarySearchTree<ElementType>::Find( const ElementType& element ) const
{
    return Find_Recursive( element, root );
}

template<class ElementType>
void BinarySearchTree<ElementType>::Insert( const ElementType& element )
{
    Insert_Recursive( element, root );
}

template<class ElementType>
void BinarySearchTree<ElementType>::Remove( const ElementType& element )
{
    root = Remove( root, element );
}

template<class ElementType>
TreeNodePtr BinarySearchTree<ElementType>::Remove( TreeNode* tree, ElementType element )
{
    if( tree == NULL )
        return NULL;

    if( element < tree->element )
        tree->left = Remove( tree->left, element );
    else if( element > tree->element )
        tree->right = Remove( tree->right, element );
    else //found
    {
        // case 1: leaf
        if( tree->left == NULL && tree->right == NULL )
        {
            delete tree;
            tree = NULL;
        }
        // case 2: 1 child
        else if( tree->left == NULL )
        {
            TreeNode* temp = tree;
            tree = tree->right;
            delete temp;
        }
        else if( tree->right == NULL )
        {
            TreeNode* temp = tree;
            tree = tree->left;
            delete temp;
        }
        // case 3: 2 children
        else
        {
            TreeNode* temp = FindMin( tree->right );
            tree->element = temp->element;
            tree->right = Remove( tree->right, temp->element );
        }
    }
    if( tree != NULL )
        tree->nodes--;

    return tree;
}

template<class ElementType>
TreeNodePtr BinarySearchTree<ElementType>::GetInOrderSuccessor( const ElementType& element ) const
{
    TreeNode* successor = NULL;
    TreeNode* node = GetNode_Recursive( element, root );

    if( node == NULL )
        return NULL;
    else if( node->right != NULL )
        successor = FindMin( node->right );
    else
    {
        TreeNode* ancestor = root;
        while( ancestor != node )
        {
            if( element < ancestor->element )
            {
                successor = ancestor;
                ancestor = ancestor->left;
            }
            else
            {
                ancestor = ancestor->right;
            }
        }
    }

    return successor;
}

template<class ElementType>
TreeNodePtr BinarySearchTree<ElementType>::GetInOrderPredecessor( const ElementType& element ) const
{
    TreeNode* predecessor = NULL;
    TreeNode* node = GetNode_Recursive( element, root );

    if( node == NULL )
        return NULL;
    else if( node->left != NULL )
        predecessor = FindMax( node->left );
    else
    {
        TreeNode* ancestor = root;
        while( ancestor != node )
        {
            if( element < ancestor->element )
                ancestor = ancestor->left;
            else
            {
                predecessor = ancestor;
                ancestor = ancestor->right;
            }
        }
    }
    std::cout << predecessor->element << std::endl;
    return predecessor;
}

template<class ElementType>
bool BinarySearchTree<ElementType>::Find_Recursive( const ElementType& element, TreeNode* tree ) const
{
    if( tree == NULL ) return false;

    if( element == tree->element )
        return true;
    else if( element < tree->element )
        return Find_Recursive( element, tree->left );
    else
        return Find_Recursive( element, tree->right );
}

template<class ElementType>
TreeNodePtr BinarySearchTree<ElementType>::GetNode_Recursive( const ElementType& element, TreeNode* tree ) const
{
    if( tree == NULL ) return NULL;

    if( element == tree->element )
        return tree;
    else if( element < tree->element )
        return GetNode_Recursive( element, tree->left );
    else
        return GetNode_Recursive( element, tree->right );
}

template<class ElementType>
void BinarySearchTree<ElementType>::Insert_Recursive( ElementType element, TreeNode*& tree )
{
    if( tree == NULL )
    {
        tree = new TreeNode( element );
        tree->right = NULL;
        tree->left = NULL;
    }
    else if( element <= tree->element )
        Insert_Recursive( element, tree->left );
    else if( element > tree->element )
        Insert_Recursive( element, tree->right );

    tree->nodes++;
}

template<class ElementType>
TreeNodePtr BinarySearchTree<ElementType>::FindMin( TreeNode* tree ) const
{
    while( tree->left != NULL )
        tree = tree->left;

    return tree;
}

template<class ElementType>
TreeNodePtr BinarySearchTree<ElementType>::FindMin_Recursive( TreeNode* tree ) const
{
    if( tree == NULL )
        return NULL;
    else if( tree->left == NULL )
        return tree;

    return FindMin_Recursive( tree->left );
}

template<class ElementType>
TreeNodePtr BinarySearchTree<ElementType>::FindMax( TreeNode* tree ) const
{
    while( tree->right != NULL )
        tree = tree->right;

    return tree;
}

template<class ElementType>
TreeNodePtr BinarySearchTree<ElementType>::FindMax_Recursive( TreeNode* tree ) const
{
    if( tree == NULL )
        return NULL;
    else if( tree->right == NULL )
        return tree;

    return FindMax_Recursive( tree->right );
}

template<class ElementType>
void BinarySearchTree<ElementType>::BFS() const
{
    BFS_( root );
}

template<class ElementType>
void BinarySearchTree<ElementType>::BFS_( TreeNode* tree ) const
{
    if( tree == NULL )
        return;

    std::queue<TreeNode*> nodeQueue;
    nodeQueue.push( tree );
    while( !nodeQueue.empty() )
    {
        TreeNode* current = nodeQueue.front();
        std::cout << current->element << " ";

        if( current->left != NULL )
            nodeQueue.push( current->left );
        if( current->right != NULL )
            nodeQueue.push( current->right );

        nodeQueue.pop();
    }
}

template<class ElementType>
void BinarySearchTree<ElementType>::DFS() const
{
    InOrder( root );
}

template<class ElementType>
void BinarySearchTree<ElementType>::PreOrder( TreeNode* tree ) const
{
    if( tree == NULL )
        return;

    std::cout << tree->element << " ";
    InOrder( tree->left );
    InOrder( tree->right );
}

template<class ElementType>
void BinarySearchTree<ElementType>::InOrder( TreeNode* tree ) const
{
    if( tree == NULL )
        return;

    InOrder( tree->left );
    std::cout << tree->element << " ";
    InOrder( tree->right );
}

template<class ElementType>
void BinarySearchTree<ElementType>::PostOrder( TreeNode* tree ) const
{
    if( tree == NULL )
        return;

    InOrder( tree->left );
    InOrder( tree->right );
    std::cout << tree->element << " ";
}

template<class ElementType>
int BinarySearchTree<ElementType>::GetHeight() const
{
    return GetHeight( root );
}

template<class ElementType>
int BinarySearchTree<ElementType>::GetHeight( TreeNode* tree ) const
{
    if( tree == NULL )
        return -1;

    return max( GetHeight( tree->left ), GetHeight( tree->right ) ) + 1;
}
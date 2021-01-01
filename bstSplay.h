//Name: Kaleab Alemu
//CSCE 3110.003/006
//Date: Oct 30 2020

#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include "dsexceptions.h"
#include <algorithm>
#include <iostream>
using namespace std;       

// BinarySearchTree class
//
// CONSTRUCTION: zero parameter
//
// ******************PUBLIC OPERATIONS*********************
// void insert( x )       --> Insert x
// void remove( x )       --> Remove x
// bool contains( x )     --> Return true if x is present
// Comparable findMin( )  --> Return smallest item
// Comparable findMax( )  --> Return largest item
// boolean isEmpty( )     --> Return true if empty; else false
// void makeEmpty( )      --> Remove all items
// void printTree( )      --> Print tree in sorted order
// ******************ERRORS********************************

template <typename Comparable>
class BinarySearchTree
{
  public:
    BinarySearchTree( ) : root{ nullptr }
    {
    }

    /**
     * Copy constructor
     */
    BinarySearchTree( const BinarySearchTree & rhs ) : root{ nullptr }
    {
        root = clone( rhs.root );
    }

    /**
     * Move constructor
     */
    BinarySearchTree( BinarySearchTree && rhs ) : root{ rhs.root }
    {
        rhs.root = nullptr;
    }
    
    /**
     * Destructor for the tree
     */
    ~BinarySearchTree( )
    {
        makeEmpty( );
    }

    /**
     * Copy assignment
     */
    BinarySearchTree & operator=( const BinarySearchTree & rhs )
    {
        BinarySearchTree copy = rhs;
        std::swap( *this, copy );
        return *this;
    }
        
    /**
     * Move assignment
     */
    BinarySearchTree & operator=( BinarySearchTree && rhs )
    {
        std::swap( root, rhs.root );       
        return *this;
    }
    
    
    /**
     * Find the smallest item in the tree.
     */
    const Comparable & findMin( ) const
    {
        if( isEmpty( ) )
            cout << "Empty tree\n";
        return findMin( root )->element;
    }

    /**
     * Find the largest item in the tree.
     */
    const Comparable & findMax( ) const
    {
        if( isEmpty( ) )
            cout << "Empty tree\n";
        return findMax( root )->element;
    }

    /**
     * Returns true if x is found in the tree.
     */
    bool contains( const Comparable & x ) const
    {
        return contains( x, root );
    }

    /**
     * Test if the tree is logically empty.
     * Return true if empty, false otherwise.
     */
    bool isEmpty( ) const
    {
        return root == nullptr;
    }

    /**
     * Print the tree contents in sorted order.
     */
    void printTree( ostream & out = cout ) const
    {
        if( isEmpty( ) )
            out << "Empty tree" << endl;
        else
        {
            out << "inorder    traversal :";
            inorder( root, out );
            out << "\npreorder   traversal :";
            preorder (root, out);
            out << "\npostorder  traversal :";
            postorder (root, out);
            out << endl;
        }
    }

    /**
     * Make the tree logically empty.
     */
    void makeEmpty( )
    {
        makeEmpty( root );
    }

    /**
     * Insert x into the tree; duplicates are ignored.
     */
    void insert(Comparable & x )
    {
        insert( x, root );
        assignParent(root);
        splay(find(x,root));
    }
     
    /**
     * Insert x into the tree; duplicates are ignored.
     */
    void insert( Comparable && x )
    {
        insert( std::move( x ), root );
        assignParent(root);
        splay(find(x,root));
    }
    
    /**
     * Remove x from the tree. Nothing is done if x is not found.
     */
    void remove( const Comparable & x )
    {
        if(root==NULL){
            cout << "Empty tree\n";
            return;
        }
        if(!contains(x))
            cout << x << " not found\n";
        else {
        remove( x, root );
        assignParent(root);
        }
        
    }
    /*
    * public splay method that accepts a comparable data type.
    */
  
  private:
    struct BinaryNode
    {
        Comparable element;
        BinaryNode *left;
        BinaryNode *right;
        BinaryNode *parent;//pointer to parent node. NULL if root.

        BinaryNode( const Comparable & theElement, BinaryNode *lt, BinaryNode *rt )
          : element{ theElement }, left{ lt }, right{ rt } { }
        
        BinaryNode( Comparable && theElement, BinaryNode *lt, BinaryNode *rt )
          : element{ std::move( theElement ) }, left{ lt }, right{ rt } { }
    };

    BinaryNode *root;


    /**
     * Internal method to insert into a subtree.
     * x is the item to insert.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void insert( const Comparable & x, BinaryNode * & t )
    {
        if( t == nullptr )
            t = new BinaryNode{ x, nullptr, nullptr };
        else if( x < t->element )
            insert( x, t->left );
        else if( t->element < x )
            insert( x, t->right );
        else
            ;  // Duplicate; do nothing
    }
    
    /**
     * Internal method to insert into a subtree.
     * x is the item to insert.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void insert( Comparable && x, BinaryNode * & t )
    {
        if( t == nullptr )
            t = new BinaryNode{ std::move( x ), nullptr, nullptr };
        else if( x < t->element )
            insert( std::move( x ), t->left );
        else if( t->element < x )
            insert( std::move( x ), t->right );
        else
            ;  // Duplicate; do nothing
    }

    /**
     * Internal method to remove from a subtree.
     * x is the item to remove.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void remove( const Comparable & x, BinaryNode * & t )
    {
        if( t == nullptr )
            return;   // Item not found; do nothing
        if( x < t->element )
            remove( x, t->left );
        else if( t->element < x )
            remove( x, t->right );
        else if( t->left != nullptr && t->right != nullptr ) // Two children
        {
            t->element = findMin( t->right )->element;
            remove( t->element, t->right );
        }
        else
        {
            BinaryNode *oldNode = t;
            t = ( t->left != nullptr ) ? t->left : t->right;
            delete oldNode;
        }
    }

    /**
     * Internal method to find the smallest item in a subtree t.
     * Return node containing the smallest item.
     */
    BinaryNode * findMin( BinaryNode *t ) const
    {
        if( t == nullptr )
            return nullptr;
        if( t->left == nullptr )
            return t;
        return findMin( t->left );
    }

    /**
     * Internal method to find the largest item in a subtree t.
     * Return node containing the largest item.
     */
    BinaryNode * findMax( BinaryNode *t ) const
    {
        if( t != nullptr )
            while( t->right != nullptr )
                t = t->right;
        return t;
    }


    /**
     * Internal method to test if an item is in a subtree.
     * x is item to search for.
     * t is the node that roots the subtree.
     */
    bool contains( const Comparable & x, BinaryNode *t ) const
    {
        if( t == nullptr )
            return false;
        else if( x < t->element )
            return contains( x, t->left );
        else if( t->element < x )
            return contains( x, t->right );
        else
            return true;    // Match
    }
/****** NONRECURSIVE VERSION*************************
    bool contains( const Comparable & x, BinaryNode *t ) const
    {
        while( t != nullptr )
            if( x < t->element )
                t = t->left;
            else if( t->element < x )
                t = t->right;
            else
                return true;    // Match

        return false;   // No match
    }
*****************************************************/

    /**
     * Internal method to make subtree empty.
     */
    void makeEmpty( BinaryNode * & t )
    {
        if( t != nullptr )
        {
            makeEmpty( t->left );
            makeEmpty( t->right );
            delete t;
        }
        t = nullptr;
    }

    /**
     * Internal methods to print a subtree rooted at t in sorted order.
     * Prints in inorder, postorder, and preorder traversal.
     */
    void inorder( BinaryNode *t, ostream & out ) const
    {
        if( t != nullptr )
        {
            inorder( t->left, out );
            out << " " << t->element;
            inorder( t->right, out );
        }
    }
    void preorder(BinaryNode* t, ostream& out) const
    {
        if(t != NULL)
        {
            out << " " << t->element;
            preorder(t->left, out);
            preorder(t->right, out);
        }
    }
    void postorder (BinaryNode* t, ostream& out) const
    {
        if(t!= NULL)
        {
            postorder (t->left,out);
            postorder (t->right, out);
            out << " " << t->element;
        }
    }

    /**
     * Internal method to clone subtree.
     */
    BinaryNode * clone( BinaryNode *t ) const
    {
        if( t == nullptr )
            return nullptr;
        else
            return new BinaryNode{ t->element, clone( t->left ), clone( t->right ) };
    }
    /*
    * Internal method that assigns the parameter's parent pointer to its parent node.
    */
    void assignParent(BinaryNode* t)
    {
        if (t==NULL)
            return;
        if (t == root)
        {
            t->parent = nullptr;
            if(t->left)
            {
                t->left->parent = t;
                assignParent(t->left);
            }
            if(t->right)
            {
                t->right->parent = t;
                assignParent(t->right);
            }
        }
        else 
        {
            if(t->left)
            {
                t->left->parent = t;
                assignParent(t->left);
            }                
            if(t->right)
                {
                    assignParent(t->right);
                    t->right->parent = t; 
                }
        }
    }
    /*
    * Internal method that rotates a parameter node with respect to its parent.
    * Uses a temporary pointer to a node variable to facilitate the rotation.
    */
    void rotate (BinaryNode* t)
    {
        if (t->parent) //check if node has a parent
        {
            if(t->parent->parent) //check if node has grandparent
            {
                if(t->parent->parent->left == t->parent) //check if parent is left child of grandparent
                {
                    if(t->parent->left == t){ //a left left scenario, so a clockwise rotation takes place.
                        BinaryNode* temp = t->parent;
                        t->parent = temp->parent;
                        t->parent->left = t;
                        temp->parent = t;
                        if (t->right) {
                            temp->left = t->right;
                            t->right->parent = temp;
                        }
                        else
                            temp->left = NULL;
                        t->right = temp;  
                    }
                    else{ //a left right scenario, so an anti-clockwise rotation takes place.
                        BinaryNode* temp = t->parent;
                        t->parent = temp->parent;
                        t->parent->left = t;
                        temp->parent = t;
                        if (t->left) {
                            temp->right = t->left;
                            t->left->parent = temp;
                        }
                        else
                            temp->right = NULL;
                        t->left = temp;                   
                    }
                }
                else{
                    if(t->parent->left == t)// a right left scenario, so a clockwise rotation takes place
                    {
                        BinaryNode* temp = t->parent;
                        t->parent = temp->parent;
                        t->parent->right = t;
                        temp->parent = t;
                        if (t->right) {
                            temp->left = t->right;
                            t->right->parent = temp;
                        }
                        else
                            temp->left = NULL;
                        t->right = temp;  
                    }
                    else{ // a right right scenario, so an anti clockwise rotation takes place.
                        BinaryNode* temp = t->parent;
                        t->parent = temp->parent;
                        t->parent->right = t;
                        temp->parent = t;
                        if (t->left) {
                            temp->right = t->left;
                            t->left->parent = temp;
                        }
                        else
                            temp->right = NULL;
                        t->left = temp;   
                    }
                }
            }
            else{ //parent is the root 
                if(t->parent->left == t){ //a left child is being rotated so a clockwise rotation takes place.
                        BinaryNode* temp = t->parent;
                        t->parent = NULL;
                        temp->parent = t;
                        if (t->right) {
                            temp->left = t->right;
                            t->right->parent = temp;
                        }
                        else
                            temp->left = NULL;
                        t->right = temp;  
                    }
                    else{ //a right child is being rotated so an anti-clockwise rotation takes place.
                        BinaryNode* temp = t->parent;
                        t->parent = NULL;
                        temp->parent = t;
                        if (t->left) {
                            temp->right = t->left;
                            t->left->parent = temp;
                        }
                        else
                            temp->right = NULL;
                        t->left = temp;                   
                    }
                root = t;  //parameter becomes new root.
            }
            
        }
        else; //parameter has no parent do nothing.
    }
    /*
    * Internal method that accepts a node pointer and splays it all the way up until it's the root.
    */
    void splay (BinaryNode* t)
    {
        if (t==NULL) //terminate function if parameter is NULL.
        {
            cout << "Cannot Splay, item not found\n";
            return;
        }
        while(t!=root){ //splay until root.
            if(t->parent->parent) //check if parent is root.
            {
                if((t->parent->parent->left == t->parent && t->parent->left == t) || (t->parent->parent->right == t->parent && t->parent->right == t))
                { //a left left or right right scenario, rotate parent about grandparent first then rotate parameter about parent.
                    rotate(t->parent);
                    rotate(t);
                }
                else{   // left right or right left scenario, rotate parameter about parent then previous grandparent (now parent).
                    rotate(t);
                    rotate(t);
                }
            }
                else //parent is root rotate about parent then splaying is finished.
                    rotate(t);
            }   
    }
    /*
    *   Internal method that finds and returns a pointer to a node 
    */
    BinaryNode* find (Comparable& x, BinaryNode* t) const
    {
         if( t == nullptr )
            return NULL;
        else if( x < t->element )
            return find( x, t->left );
        else if( t->element < x )
            return find( x, t->right );
        else
            return t;
    }
    BinaryNode* find (Comparable&& x, BinaryNode* t) const
    {
         if( t == nullptr )
            return NULL;
        else if( x < t->element )
            return find( std::move(x), t->left );
        else if( t->element < x )
            return find( std::move(x), t->right );
        else
            return t;
    }
};

#endif


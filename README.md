# splay-tree
This program demonstrates a splay tree using a binary node and recursion. It implements the divide and conquer method and has a runtime time complexity of O(n)

It uses the provided code in bstSplay.h and adds some methods like rotate, splay, assignParent and find to execute the splay tree.
The code basically runs when compiled as g++ project.cpp bstSplay.h . The assignParent goes node to node and assigns the parent pointer variable of every node to its pointer node. 
The rotate accepts a node and rotates it about its parent.
The splay function accepts a node parameter and splays it all the way up the tree and makes it the root.
The find accepts a comparable parameter and returns the node where it is located.  

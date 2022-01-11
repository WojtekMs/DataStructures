# Binary Search Tree
This is basic implementation of Binary Search Tree. Currently, not all functions are implemented, but project will be (hopefully) further developed in the future. Binary Search Tree is a sorted & hierarchical container, which allows for faster element look and element insertion. However, time complexity of both of the mentioned functions is dependent on the tree balance. It is essential that the tree is well balanced in order to keep the complexity low. There are implementations of self-balancing trees that can do this automatically and they are called 'Red Black Trees' (for example `std::map`). 

Implemented functions:
- [Tree Height](#tree-height)
- [Node depth](#node-depth)
- [Find element](#find-element)
- [Insert element](#insert-element)
- [In order traversal](#in-order-traversal)
- [Post order traversal](#post-order-traversal)
## Tree Height
Tree Height is measured from the lowest node to the heighest node (root). The heighest element in the tree is the root.  

The basic algorithm for tree height computation is:
- if node does not exist then return 0 (neutral sum element)
- if node is a leaf (has no children), then it is a base case with height 1
- if node has children, it's height is 1 + left_children or right_children (we have to choose the greater value of left / right children)

Time Complexity: O(N) where N is the number of elements

## Node depth
The depth of a node is the total number of edges from the root node to the selected node.

Implemented algorithm:
- if selected node is root return 0
- if node has a parent then it's depth is 1 + parent depth

This implementation assumes your BST Nodes contain pointers to parent nodes.  

Time Complexity: O(P) where P is the number of parent nodes relative to chosen node

## Find element
In order to find the right node it is necessary to start the search from the root node. Based on the current node value the search is continued in the left half of the tree or in the right half of the tree. If the tree is balanced (approximately both sides of the tree have the same size) then the search has logarithmic time complexity, because in each step you decrease the tree by half.  

Implemented algorithm:
- if the current node is null then throw `NoElementError`
- if the target value is greater than current node value search in the right half of the tree (`find(current->right_child, val)`)
- if the target value is less than current node value search in the left half of the tree (`find(current->left_child, val)`)
- if none of the above then result is the current node


Time Complexity: average O(logN) where N is the number of elements; if the tree is unbalanced it can go as bad as O(N)

## Insert element
Because Binary Search Tree is a sorted container you have to find the right place for the new element (to keep the container in valid state). Insertion is similar to finding element, with the exception that if the current node is null, then it is the right place to insert new element.

Implemented algorithm:
- if the current node is null then use `new` expression to assign address and initialize Node
- if the element value is greater than current node value insert in the right half of the tree (`insert(current->right_child, val)`)
- if the element value is less than current node value search in the left half of the tree (`insert(current->left_child, val)`)

NOTE: It is important to note that C++ has value-semantics, so when you pass a pointer to a function you pass a copy of the pointer. You cannot assign new address to the copy of the pointer directly. It is necessary to use either pointer-to-pointer or a reference to a pointer, in order to avoid the copy.

Time Complexity: average O(logN) where N is the number of elements; if the tree is unbalanced it can go as bad as O(N)

## In order traversal
In order traversal is a helper algorithm that can be used to implement other useful methods of Binary Search Tree (for example: print). 'Traversal' means that the algorithm will pass through and apply given function to every element of the tree (will traverse the tree). 'In order' means that the function will be applied starting with the element with the lowest value and will progress to the next element with a bit greater value. It will be performed in a sorted order (that is why it's called in order, because it is applied in the most natural order).

Implementation:
- if the current node is null then return
- apply inOrderTraversal to the left child
- apply a function
- apply inOrderTraversal to the right child  
**The above sequence will be applied to each child, hence affecting every element of the tree in this precise order**

Time Complexity: O(N) where N is the number of elements

## Post order traversal
Post order traversal is very similar to in order traversal. The only difference is (as the name suggest) the order of applying the function to each element. Post order will first access the lowest element in the tree and then start to apply the function from the bottom up. This function can be used to delete the entire tree (if you start deleting the tree from the first element you will loose the handle to next elements).

Implementation:
- if the current node is null then return
- apply postOrderTraversal to the left child
- apply postOrderTraversal to the right child
- apply a function  
**The above sequence will be applied to each child, hence affecting every element of the tree in this precise order**

Time Complexity: O(N) where N is the number of elements

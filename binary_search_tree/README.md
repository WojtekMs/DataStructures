Basic implementation of Binary Search Tree  
Functions:
- post order traversal (used to delete all the allocated memory)
- in order traversal (used to print the tree)
- element insertion (logarithmic time complexity on average)
- element lookup (logarthimic time complexity on average)
- node depth computation (linear time complexity == number of parent
    nodes relative to chosen node)
- tree height computation (linear time complexity == total number of
    elements in the tree)

# Tree Height
Tree Height is measured from the lowest node to the heighest node (root). The heighest element in the tree is the root.  
The basic algorithm for tree height computation is:
- if node does not exist then return 0 (neutral sum element)
- if node is a leaf (has no children), then it is a base case with height 1
- if node has children, it's height is 1 + left_children or right_children (we have to choose the greater value of left / right children)

Time Complexity: O(N) where N is the number of elements

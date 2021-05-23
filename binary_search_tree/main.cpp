#include "BST.hpp"
#include <iostream>

int main() {
    BST<int> tree;
    tree.insert(12);
    tree.insert(8);
    tree.insert(11);
    tree.insert(10);
    tree.insert(13);
    tree.insert(9);

    std::cout << tree.getHeight() << '\n';
    std::cout << tree.getDepth(tree.findNode(9)) << '\n';

    
    tree.printNode(tree.root());
    std::cout << "\n";
    // tree.printNode(tree.findNode(17));
}

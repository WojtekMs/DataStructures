#pragma once
#include "NoElementError.hpp"

#include <functional>
#include <iostream>
#include <vector>

template <typename ValueType>
class BST
{
    struct Node {
        Node* left_child_{};
        Node* right_child_{};
        Node* parent_{};
        ValueType value_{};
        explicit Node(ValueType val);
        bool isLeaf() const;
    };
    Node* root_{};
    int size_{};

    Node* findParent(Node* current, ValueType val) const;
    int countChildrenHeight(const Node* current) const;
    void postOrderTraversal(Node*, std::function<void(Node*)>);
    void constInOrderTraversal(const Node*, std::function<void(const Node*)>) const;
    template <typename Value>
    void insert(Value&&, Node**);

   public:
    BST() = default;
    ~BST();
    template <typename Value>
    void insert(Value&& val);
    void printNode(const Node* current) const;
    template <typename Value>
    const Node* findNode(Value&& val) const;
    const Node* root() const;
    int getDepth(const Node* node) const;
    int getHeight() const;
    int getSize() const;
};

template <typename ValueType>
BST<ValueType>::Node::Node(ValueType val) : value_(val)
{
}

template <typename ValueType>
bool BST<ValueType>::Node::isLeaf() const
{
    return (!right_child_ && !left_child_);
}

template <typename ValueType>
template <typename Value>
void BST<ValueType>::insert(Value&& val, Node** node)
{
    if (!*node) {
        *node = new Node(val);
        size_++;
        return;
    }
    if (val < (*node)->value_) {
        insert(std::forward<Value>(val), &((*node)->left_child_));
    }
    if (val > (*node)->value_) {
        insert(std::forward<Value>(val), &((*node)->right_child_));
    }
}

// Complexity: O(logN) where N is the number of elements
template <typename ValueType>
template <typename Value>
void BST<ValueType>::insert(Value&& val)
{
    insert(std::forward<Value>(val), &root_);
}

// returns the parent of the potential node with value "val"
// if there is already element with value "val" return the pointer to this element
// Complexity: O(h) where h is the height of the tree
// (which means O(logn) on average where n is the total number of elements in the tree)
// Worst case scenario: O(n) where n is the total number of elements in the tree
template <typename ValueType>
typename BST<ValueType>::Node* BST<ValueType>::findParent(Node* current,
                                                          ValueType val) const
{
    if (current->left_child_ && val < current->value_) {
        current = findParent(current->left_child_, val);
    }
    if (current->right_child_ && val > current->value_) {
        current = findParent(current->right_child_, val);
    }
    return current;
}

// Complexity O(n) where n is the total number of elements in the tree
template <typename ValueType>
void BST<ValueType>::printNode(const BST<ValueType>::Node* current) const
{
    auto print = [](auto currentNode) { std::cout << currentNode->value_ << ", "; };
    constInOrderTraversal(current, print);
}

template <typename ValueType>
const typename BST<ValueType>::Node* BST<ValueType>::root() const
{
    return root_;
}

template <typename ValueType>
template <typename Value>
const typename BST<ValueType>::Node* BST<ValueType>::findNode(Value&& val) const
{
    if (!root_) {
        throw NoElementError(std::forward<Value>(val));
    }
    auto current = findParent(root_, val);
    if (current->value_ == val) {
        return current;
    }
    throw NoElementError(std::forward<Value>(val));
}

// returns the depth of the chosen node, starting with 1 at the root node
// Complexity: O(n) where n is the number of parents of the chosen node
// In the worst case scenario n = total number of elements (unbalanced tree)
template <typename ValueType>
int BST<ValueType>::getDepth(const BST<ValueType>::Node* node) const
{
    if (node == nullptr) {
        return 0;
    }
    if (node == root_) {
        return 1;
    }
    return getDepth(node->parent_) + 1;
}

template <typename ValueType>
int BST<ValueType>::getHeight() const
{
    if (!root_) {
        return 0;
    }
    return countChildrenHeight(root_);
}

template <typename ValueType>
int BST<ValueType>::getSize() const
{
    return size_;
}

// if we find a leaf, then it is a base case with height 1
// if a node has children, it's height is 1 + count of left or right child's children
// we have to choose the greater value of that
// Complexity: O(n) where n is the total number of elements in the tree
template <typename ValueType>
int BST<ValueType>::countChildrenHeight(const BST<ValueType>::Node* current) const
{
    if (current->isLeaf()) {
        return 1;
    }
    int leftChildrenHeight = 0;
    int rightChildrenHeight = 0;
    if (current->left_child_) {
        leftChildrenHeight = 1 + countChildrenHeight(current->left_child_);
    }
    if (current->right_child_) {
        rightChildrenHeight = 1 + countChildrenHeight(current->right_child_);
    }
    return std::max(rightChildrenHeight, leftChildrenHeight);
}

template <typename ValueType>
void BST<ValueType>::postOrderTraversal(
    BST<ValueType>::Node* current,
    std::function<void(BST<ValueType>::Node*)> function)
{
    if (!current) {
        return;
    }
    if (current->left_child_) {
        postOrderTraversal(current->left_child_, function);
    }
    if (current->right_child_) {
        postOrderTraversal(current->right_child_, function);
    }
    function(current);
}

template <typename ValueType>
void BST<ValueType>::constInOrderTraversal(
    const BST<ValueType>::Node* current,
    std::function<void(const BST<ValueType>::Node*)> function) const
{
    if (!current) {
        return;
    }
    if (current->left_child_) {
        constInOrderTraversal(current->left_child_, function);
    }
    function(current);
    if (current->right_child_) {
        constInOrderTraversal(current->right_child_, function);
    }
}

template <typename ValueType>
BST<ValueType>::~BST()
{
    postOrderTraversal(root_, [](auto current) { delete current; });
}

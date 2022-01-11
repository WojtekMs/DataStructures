#pragma once
#include "NoElementError.hpp"

#include <functional>
#include <iostream>
#include <memory>

template <typename ValueType>
class BST
{
    struct Node {
        Node* left_child_{};
        Node* right_child_{};
        Node* parent_{};
        ValueType value_{};
        template <typename Value>
        explicit Node(Value&& val);
        bool isLeaf() const;
    };
    Node* root_{};
    int size_{};

    Node* findParent(Node* current, ValueType val) const;
    void postOrderTraversal(Node*, std::function<void(Node*)>);
    void constInOrderTraversal(const Node*, std::function<void(const Node*)>) const;
    int countHeight(const Node*) const;
    
    template <typename Value>
    void insert(Value&&, Node**);

    template <typename Value>
    const Node* findNode(Value&&, const Node*) const;

   public:
    BST() = default;
    ~BST();
    
    template <typename Value>
    void insert(Value&& val);
    
    template <typename Value>
    const Node* findNode(Value&& val) const;

    const Node* root() const;
    int getDepth(const Node* node) const;
    int countHeight() const;
    int getSize() const;
    void printNode(const Node* current) const;
};

template <typename T>
template <typename Value>
BST<T>::Node::Node(Value&& val) : value_(std::forward<Value>(val))
{
}

template <typename T>
bool BST<T>::Node::isLeaf() const
{
    return (!right_child_ && !left_child_);
}

template <typename T>
template <typename Value>
void BST<T>::insert(Value&& val, Node** node)
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
template <typename T>
template <typename Value>
void BST<T>::insert(Value&& val)
{
    insert(std::forward<Value>(val), &root_);
}

// returns the parent of the potential node with value "val"
// if there is already element with value "val" return the pointer to this element
// Complexity: O(h) where h is the height of the tree
// (which means O(logn) on average where n is the total number of elements in the tree)
// Worst case scenario: O(n) where n is the total number of elements in the tree
template <typename T>
typename BST<T>::Node* BST<T>::findParent(Node* current, T val) const
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
template <typename T>
void BST<T>::printNode(const BST<T>::Node* current) const
{
    auto print = [](auto currentNode) { std::cout << currentNode->value_ << ", "; };
    constInOrderTraversal(current, print);
}

template <typename T>
const typename BST<T>::Node* BST<T>::root() const
{
    return root_;
}

template <typename T>
template <typename Value>
const BST<T>::Node* BST<T>::findNode(Value&& val, const BST<T>::Node* node) const
{
    if (!node) {
        throw NoElementError(val);
    }
    auto result = node;
    if (val > node->value_) {
        result = findNode(std::forward<Value>(val), node->right_child_);
    }
    if (val < node->value_) {
        result = findNode(std::forward<Value>(val), node->left_child_);
    }
    return result;
}

// Complexity: O(logN) where N is the number of elements
template <typename T>
template <typename Value>
const typename BST<T>::Node* BST<T>::findNode(Value&& val) const
{
    return findNode(std::forward<Value>(val), root_);
}

// returns the depth of the chosen node, starting with 1 at the root node
// Complexity: O(n) where n is the number of parents of the chosen node
// In the worst case scenario n = total number of elements (unbalanced tree)
template <typename T>
int BST<T>::getDepth(const BST<T>::Node* node) const
{
    if (node == nullptr) {
        return 0;
    }
    if (node == root_) {
        return 1;
    }
    return getDepth(node->parent_) + 1;
}

template <typename T>
int BST<T>::countHeight() const
{
    return countHeight(root_);
}

template <typename T>
int BST<T>::getSize() const
{
    return size_;
}


// Complexity: O(n) where n is the total number of elements in the tree
template <typename T>
int BST<T>::countHeight(const BST<T>::Node* current) const
{
    if (!current) {
        return 0;
    }
    if (current->isLeaf()) {
        return 1;
    }
    return 1 + std::max(countHeight(current->left_child_), countHeight(current->right_child_));
}

template <typename T>
void BST<T>::postOrderTraversal(BST<T>::Node* current,
                                std::function<void(BST<T>::Node*)> function)
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

template <typename T>
void BST<T>::constInOrderTraversal(
    const BST<T>::Node* current,
    std::function<void(const BST<T>::Node*)> function) const
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

template <typename T>
BST<T>::~BST()
{
    postOrderTraversal(root_, std::default_delete<BST<T>::Node>{});
}

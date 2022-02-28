#include <iostream>
#include <utility>

template <typename T>
class ForwardList
{
    struct Node {
        Node* next_{};
        T value_{};

        explicit Node(const T& value);
    };

   public:
    void insert(const T& value);
    void reverse();
    void print();

    const Node* head() const;

   private:
    void reverse(Node*& first, Node* last, int current);

    int size_{};
    Node* head_{};
};

template <typename T>
ForwardList<T>::Node::Node(const T& value) : value_(value) {}

template <typename T>
void ForwardList<T>::insert(const T& value)
{
    if (!head_) {
        head_ = new Node{value};

    } else {
        auto* current = head_;
        while (current->next_) {
            current = current->next_;
        }
        current->next_ = new Node{value};
    }
    size_++;
}

template <typename T>
void ForwardList<T>::print()
{
    auto* current = head_;
    while (current) {
        std::cout << current->value_ << " ";
        current = current->next_;
    }
    std::cout << "\n";
}

template <typename T>
void ForwardList<T>::reverse()
{
    auto* head_copy = head_;
    reverse(head_copy, head_, 0);
}

template <typename T>
void ForwardList<T>::reverse(Node*& first, Node* last, int current)
{
    if (!first || !last) {
        return;
    }
    reverse(first, last->next_, current + 1);
    if (current >= size_ / 2) {
        std::swap(first->value_, last->value_);
        first = first->next_;
    }
}

// since C++20 typename before dependent type is not required
template <typename T>
const typename ForwardList<T>::Node* ForwardList<T>::head() const
{
    return head_;
}

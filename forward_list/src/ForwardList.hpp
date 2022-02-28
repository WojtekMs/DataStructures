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
    ForwardList() = default;
    ForwardList(const ForwardList& rhs);
    ForwardList(ForwardList&& rhs) = delete;
    ForwardList& operator=(const ForwardList& rhs) = delete;
    ForwardList& operator=(ForwardList&& rhs) = delete;
    ~ForwardList();

    void insert(const T& value);
    void reverse();
    void print();

    [[nodiscard]] const Node* head() const;
    [[nodiscard]] int size() const;

   private:
    void reverse(Node*& first, Node* last, int current);

    int size_{};
    Node* head_{};
};

template <typename T>
ForwardList<T>::Node::Node(const T& value) : value_(value)
{
}

template <typename T>
ForwardList<T>::ForwardList(const ForwardList& rhs) : size_(rhs.size_)
{
    if (!head_ && rhs.head_) {
        head_ = new Node(rhs.head_->value_);
    }
    const auto* rhsCurrent = rhs.head_->next_;
    auto* lhsCurrent = head_;
    while (rhsCurrent) {
        lhsCurrent->next_ = new Node(rhsCurrent->value_);
        lhsCurrent = lhsCurrent->next_;
        rhsCurrent = rhsCurrent->next_;
    }
}

template <typename T>
ForwardList<T>::~ForwardList()
{
    while (head_) {
        auto* copy = head_;
        head_ = head_->next_;
        delete copy;
    }
}

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

template <typename T>
int ForwardList<T>::size() const
{
    return size_;
}

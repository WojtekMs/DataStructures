# How to reverse forward list?

It is possible to do this using recursion in O(n) time.
```cpp
class ForwardList {
  public:
    void reverse(Node*& first, Node* last, int current) {
        if (!first || !last) {
            return;
        }
        reverse(first, last->next, current + 1);
        if (current >= size_ / 2) {
            std::swap(first->value, last->value);
            first = first->next;
        }
    }

  private:
    int size_{};
};

```

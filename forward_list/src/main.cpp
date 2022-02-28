#include "ForwardList.hpp"

int main() {
    ForwardList<int> l;
    l.insert(1);
    l.insert(2);
    l.insert(1);
    l.insert(5);
    l.insert(97);
    l.print();
    l.reverse();
    l.print();
}

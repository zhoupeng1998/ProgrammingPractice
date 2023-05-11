#include <iostream>
#include <iterator>

// Please refer to "Effective C++" item 47

template <typename T>
class MyVector {
public:
    class iterator {
    public:
        typedef std::random_access_iterator_tag iterator_category;
        // iterator implementations
    };

    // implementations
};

template <typename T>
class MyList {
public:
    class iterator {
    public:
        typedef std::bidirectional_iterator_tag iterator_category;
        // iterator implementations
    };

    // implementations
};

namespace std {

template <typename IterT>
struct iterator_traits<MyVector<IterT>> {
    typedef std::random_access_iterator_tag iterator_category;
};

template <typename IterT>
struct iterator_traits<MyList<IterT>> {
    typedef std::bidirectional_iterator_tag iterator_category;
};

}

template <typename IterT, typename DistT>
void advance(IterT& iter, DistT d) {
    doAdvance(iter, d, typename std::iterator_traits<IterT>::iterator_category());
}

template <typename IterT, typename DistT>
void doAdvance(IterT& iter, DistT d, std::random_access_iterator_tag) {
    std::cout << "random access iterator!" << std::endl;
    // random access iterator
}

template <typename IterT, typename DistT>
void doAdvance(IterT& iter, DistT d, std::bidirectional_iterator_tag) {
    std::cout << "bidirectional iterator!" << std::endl;
    // bidirectional iterator
}

int main() {
    MyVector<int> v1;
    MyList<int> l1;
    advance(v1, 1);
    advance(l1, 1);
    return 0;
}
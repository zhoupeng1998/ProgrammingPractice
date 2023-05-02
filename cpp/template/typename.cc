#include <iostream>
#include <vector>

// based on C++ Primer 5th Edition, item 42

// base class list, initializer list shall not use typename

template <typename T>
void print2nd(const T& container)
// if you want to use T::const_iterator in argument, you must use typename too
{
    // can use "typedef typename" to define a type
    if (container.size() >= 2)
    {
        // typename is required to tell the compiler that T::const_iterator is a type
        typename T::const_iterator iter(container.begin());
        ++iter;
        int value = *iter;
        std::cout << value << std::endl;
    }
}

int main()
{
    std::vector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    print2nd(vec);
    return 0;
}

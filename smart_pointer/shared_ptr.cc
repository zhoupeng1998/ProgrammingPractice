#include "shared_ptr.h"

namespace ZP 
{

template <typename T>
shared_ptr<T>::shared_ptr(T* p)
    :ptr(p), ref_count(new int(0))
{
    if (p) {
        (*ref_count)++;
    }
}

template <typename T>
shared_ptr<T>::shared_ptr(const shared_ptr<T>& p)
    :ptr(p.ptr), ref_count(p.ref_count)
{
    if (p.ptr) {
        (*ref_count)++;
    }
}


template <typename T>
shared_ptr<T>::~shared_ptr()
{
    if (ref_count) {
        (*ref_count)--;
        if (ptr && *ref_count == 0) {
            delete ptr;
            ptr = nullptr;
        }
    }
}

template <typename T>
T& shared_ptr<T>::operator*()
{
    return *ptr;
}

template <typename T>
T* shared_ptr<T>::operator->()
{
    return ptr;
}

template class shared_ptr<int>;

}
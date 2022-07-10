#ifndef _SHARED_PTR_H_
#define _SHARED_PTR_H_

namespace ZP
{

template <typename T>
class shared_ptr
{
private:
    T* ptr;
    int* ref_count;
public:
    shared_ptr(T* ptr);
    shared_ptr(const shared_ptr<T>& ptr);
    ~shared_ptr();

    T& operator*();
    T* operator->();
};

} // namespace ZP

#endif
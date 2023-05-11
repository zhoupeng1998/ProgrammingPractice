#ifndef SHARED_PTR_H_
#define SHARED_PTR_H_

template <typename T>
class SharedPtr {
public:
    SharedPtr(const SharedPtr& rhs);

    template <typename U>
    SharedPtr(const SharedPtr<U>& rhs);

    SharedPtr& operator=(const SharedPtr& rhs);

    template <typename U>
    SharedPtr& operator=(const SharedPtr<U>& rhs);
};

#endif
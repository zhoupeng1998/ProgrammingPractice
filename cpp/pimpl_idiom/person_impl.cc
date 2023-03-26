#include "person_impl.h"

#include <string>

PersonImpl::PersonImpl(const std::string& name, int age)
    :name_(name), age_(age)
{
}

PersonImpl::~PersonImpl()
{
}

std::string PersonImpl::name() const
{
    return name_;
}

int PersonImpl::age() const
{
    return age_;
}
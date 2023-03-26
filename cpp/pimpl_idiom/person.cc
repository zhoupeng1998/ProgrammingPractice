#include "person_impl.h"
#include "person.h"

Person::Person()
    :pImpl(new PersonImpl("", 0))
{
}

Person::Person(const std::string& name, int age)
    :pImpl(new PersonImpl(name, age))
{
}

Person::~Person()
{
}

std::string Person::name() const
{
    return pImpl->name();
}

int Person::age() const
{
    return pImpl->age();
}
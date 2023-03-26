#include <string>

#include "real_person.h"

RealPerson::RealPerson(const std::string& name, int age)
    :name_(name), age_(age)
{
}

RealPerson::~RealPerson()
{
}

std::string RealPerson::name() const
{
    return name_;
}

int RealPerson::age() const
{
    return age_;
}
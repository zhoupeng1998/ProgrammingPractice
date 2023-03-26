#include "person.h"
#include "real_person.h"

Person::~Person()
{
}

std::unique_ptr<Person> Person::create(const std::string& name, int age)
{
    return std::unique_ptr<Person>(new RealPerson(name, age));
}
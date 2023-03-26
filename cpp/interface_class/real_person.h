#ifndef REAL_PERSON_H_
#define REAL_PERSON_H_

#include <string>

#include "person.h"

class RealPerson : public Person
{
public:
    RealPerson(const std::string& name, int age);
    virtual ~RealPerson();

    std::string name() const;
    int age() const;

private:
    std::string name_;
    int age_;
};

#endif
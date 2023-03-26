#ifndef PERSON_IMPL_H_
#define PERSON_IMPL_H_

#include <string>

class PersonImpl
{
public:
    PersonImpl(const std::string& name, int age);
    ~PersonImpl();

    std::string name() const;
    int age() const;

private:
    std::string name_;
    int age_;
};

#endif
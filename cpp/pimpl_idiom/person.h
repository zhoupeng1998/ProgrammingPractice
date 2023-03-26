#ifndef PERSON_H_
#define PERSON_H_

#include <string>
#include <memory>

class PersonImpl;

class Person
{
public:
    Person();
    Person(const std::string& name, int age);
    ~Person();

    std::string name() const;
    int age() const;

private:
    std::unique_ptr<PersonImpl> pImpl;
};

#endif
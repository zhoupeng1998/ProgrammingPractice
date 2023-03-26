#ifndef PERSON_H_
#define PERSON_H_

#include <string>
#include <memory>

class Person
{
public:
    virtual ~Person();

    virtual std::string name() const = 0;
    virtual int age() const = 0;

    static std::unique_ptr<Person> create(const std::string& name, int age);
};

#endif
package intro

import "fmt"

type person struct {
	Name   string
	age    int
	salary float64
}

func NewPerson(name string, age int, salary float64) *person {
	return &person{
		Name:   name,
		age:    age,
		salary: salary,
	}
}

func (p *person) GetName() string {
	return p.Name
}

func (p *person) SetName(name string) {
	p.Name = name
}

func (p *person) GetAge() int {
	return p.age
}

func (p *person) SetAge(age int) {
	if age >= 0 && age <= 150 {
		p.age = age
	} else {
		fmt.Println("Invalid age")
		p.age = 0
	}
}

func (p *person) GetSalary() float64 {
	return p.salary
}

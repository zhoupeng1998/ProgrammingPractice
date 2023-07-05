package intro

import "fmt"

type Person struct {
	Age int
	Sex string
}

type Student struct {
	Name  string
	Age   int
	Score int
}

type ElementaryStudent struct {
	Student
	Grade int
}

type GradStudent struct {
	Person
	Student
	Grade int
}

func (s *Student) GetName() string {
	return s.Name
}

func (s *Student) SetScore(score int) {
	s.Score = score
}

func (s *ElementaryStudent) Test() {
	fmt.Println("elementary student testing")
}

func (s *GradStudent) Test() {
	fmt.Println("grad student testing")
}

func (s *GradStudent) SetScore(score int) {
	fmt.Println("curved!")
	s.Score = score + 10
}

func DoInheritance() {
	var s0 *ElementaryStudent = &ElementaryStudent{
		Student: Student{
			Name:  "Tom",
			Age:   10,
			Score: 100,
		},
		Grade: 5,
	}
	s0.Test()
	s0.SetScore(90)
	s0.Grade = 4
	fmt.Println(s0)

	var s1 *GradStudent = &GradStudent{
		Person: Person{
			Age: 20,
			Sex: "M",
		},
		Student: Student{
			Name:  "Jerry",
			Age:   20,
			Score: 100,
		},
		Grade: 5,
	}
	s1.Test()
	s1.SetScore(90)
	//s1.Student.SetScore(90) // call parent's method
	s1.Person.Age = 30 // must specify parent in multiple inheritance
	fmt.Println(s1)

}

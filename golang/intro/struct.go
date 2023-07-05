package intro

import (
	"encoding/json"
	"fmt"
)

type Cat struct {
	Name  string `json:"name"` // tag
	Age   int    `json:"age"`
	color string
}

type Fun struct {
	f0 bool
	f1 int32
	f2 string
	f3 int
	f4 string
}

// factory method
func NewCat(name string, age int, color string) *Cat {
	return &Cat{
		Name:  name,
		Age:   age,
		color: color,
	}
}

// getter if name is not exported
func (cat *Cat) GetName() string {
	return cat.Name
}

// method
func (cat Cat) Eat() {
	fmt.Println(cat.Name, "is eating")
	cat.Age++
}

func (cat *Cat) Eat2(food string) {
	fmt.Println(cat.Name, "is eating", food)
	cat.Age++
}

// "toString" method
func (cat Cat) String() string {
	return fmt.Sprintf("%s\t%d\t%s", cat.Name, cat.Age, cat.color)
}

func DoStruct() {
	var cat0 Cat
	cat0.Name = "Tom"
	cat0.Age = 3
	cat0.color = "blue"

	cat1 := new(Cat)
	cat1.Name = "Tom"
	cat1.Age = 3
	cat1.color = "blue"

	fmt.Printf("%T %v\n", cat0, cat0)
	fmt.Printf("%T %v\n", cat1, cat1)
	fmt.Println(cat0.Name, cat0.Age, cat0.color)

	fmt.Printf("%p %p %p %p\n", &cat0, &cat0.Name, &cat0.Age, &cat0.color)
	fmt.Printf("%p %p %p %p\n", &cat1, &cat1.Name, &cat1.Age, &cat1.color)

	cat2 := Cat{"Tom", 3, "blue"}
	fmt.Printf("%T %v\n", cat2, cat2)

	cat3 := &Cat{"Tom", 3, "blue"}
	fmt.Printf("%T %v\n", cat3, cat3)

	cat4 := cat2
	cat4.Name = "Jerry"
	fmt.Println(cat2, cat4)

	cat5 := cat3
	cat5.Name = "Jerry"
	fmt.Println(cat3, cat5)

	// can use "cat5.Eat()" for method, but must use "&cat5" for function
	cat5.Eat()
	fmt.Println(cat5)
	cat5.Eat2("fish")
	fmt.Println(cat5)
}

func DoStructMem() {
	fun := Fun{false, 1, "2", 3, "4"}
	fmt.Printf("%p %p %p %p %p\n", &fun.f0, &fun.f1, &fun.f2, &fun.f3, &fun.f4)
}

func DoSerialize() {
	cat := Cat{"Tom", 3, "blue"}
	jsoncat, err := json.Marshal(cat)
	fmt.Printf("%T %v %v\n", jsoncat, string(jsoncat), err)
}

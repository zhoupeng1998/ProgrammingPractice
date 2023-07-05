package reflection

import (
	"fmt"
	"reflect"
)

type Cat struct {
	Name string
	Age  int
}

type Student struct {
	Name string
	Age  int
}

// can convert between value <-> interface{} <-> reflect.Value
// use type assertion to convert interface{} to concrete type
func reflectInt(b interface{}) {
	// get reflect.Type
	rType := reflect.TypeOf(b)
	fmt.Println("rType=", rType)

	// get reflect.Value
	rVal := reflect.ValueOf(b)
	fmt.Println("rVal=", rVal)

	//n1 := 10
	//n2 := 2 + rVal // invalid, mismatched type (rVal is reflect.Value)
	n2 := 2 + rVal.Int() // must match type, otherwise panic
	fmt.Println("n2=", n2)

	// convert reflect.Value to interface{}
	iV := rVal.Interface()
	// convert interface{} to int
	num2 := iV.(int)
	fmt.Println("num2=", num2)
}

func reflectStruct(b interface{}) {
	rType := reflect.TypeOf(b)
	fmt.Println("rType=", rType)

	rVal := reflect.ValueOf(b)
	fmt.Println("rVal=", rVal)

	iV := rVal.Interface()

	switch v := iV.(type) {
	case Cat:
		fmt.Printf("iV=%v, type=%T, name=%v\n", iV, iV, v.Name)
	case Student:
		fmt.Printf("iV=%v, type=%T, name=%v\n", iV, iV, v.Name)
	default:
		fmt.Println("Unknown")
	}
}

func reflectKind(b interface{}) {
	rType := reflect.TypeOf(b)
	fmt.Println("rType=", rType)

	rVal := reflect.ValueOf(b)
	fmt.Println("rVal=", rVal)

	kind1 := rVal.Kind()
	kind2 := rType.Kind()
	fmt.Println("kind1=", kind1, "kind2=", kind2)
}

func DoReflect() {
	var num int = 10
	reflectInt(num)

	var cat Cat = Cat{"Tom", 5}
	reflectStruct(cat)

	var stu Student = Student{"Tom", 5}
	reflectStruct(stu)
}

func DoReflectKind() {
	var num int = 10
	reflectKind(num)

	var cat Cat = Cat{"Tom", 5}
	reflectKind(cat)
}

func reflectSetInt(b interface{}) {
	//rTyp := reflect.TypeOf(b)
	rVal := reflect.ValueOf(b)
	//rVal.SetInt(20) // wrong because it's pointer
	rVal.Elem().SetInt(20) // elem() to get concrete value
}

func DoReflectSet() {
	var num int = 10
	reflectSetInt(&num)
	fmt.Println("num=", num)
}

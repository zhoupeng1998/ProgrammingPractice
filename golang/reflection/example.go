package reflection

import (
	"fmt"
	"reflect"
)

type Monster struct {
	Name  string `json:"name"`
	Age   int    `json:"monster_age"`
	Score float32
	Sex   string
}

func (s *Monster) Print() {
	fmt.Println("---start---")
	fmt.Println(s)
	fmt.Println("---end---")
}

func (s *Monster) GetSum(n1, n2 int) int {
	return n1 + n2
}

func (s *Monster) Set(name string, age int, score float32, sex string) {
	s.Name = name
	s.Age = age
	s.Score = score
	s.Sex = sex
}

func TestStruct(a interface{}) {
	typ := reflect.TypeOf(a)
	val := reflect.ValueOf(a)
	ptr := reflect.PtrTo(typ)
	kd := val.Kind()
	if kd != reflect.Struct || (kd == reflect.Ptr && typ.Elem().Kind() != reflect.Struct) {
		fmt.Println("expect struct")
		fmt.Println("kd=", kd)
		return
	}
	num := val.NumField()
	fmt.Printf("struct has %d fields\n", num)
	for i := 0; i < num; i++ {
		fmt.Printf("Field %d: value=%v\n", i, val.Field(i))
		tagVal := typ.Field(i).Tag.Get("json")
		if tagVal != "" {
			fmt.Printf("\tField %d: tag=%v\n", i, tagVal)
		}
	}
	// *Monster method doen't count
	numOfMethod := val.NumMethod()
	fmt.Printf("struct has %d methods\n", numOfMethod)

	numOfPtrMethod := ptr.NumMethod()
	fmt.Printf("struct has %d pointer methods\n", numOfPtrMethod)

	// calling method without params
	// method order: ascii alphabetical
	val.Method(1).Call(nil) // call the 2nd method

	// calling method with params
	var params []reflect.Value
	params = append(params, reflect.ValueOf(10))
	params = append(params, reflect.ValueOf(40))
	res := val.Method(0).Call(params)
	fmt.Printf("res=%v\n", res[0].Int())
}

func DoReflectExample() {
	var a Monster = Monster{
		Name:  "Tom",
		Age:   30,
		Score: 99.9,
	}
	TestStruct(a)
}

package intro

import (
	"fmt"
	"strconv"
	"unsafe"
)

func DoVar() {
	var a int // if not assign value, set to default value
	a = 1
	var b = 2 // detect type automatically
	c := 3    // must not declared before, otherwise error

	var n1, n2 = "hello", 1.3
	//n1 = 1 // error

	fmt.Println(a, b, c)
	fmt.Println(n1, n2)
	fmt.Printf("n1 type is %T, size is %d\n", n1, unsafe.Sizeof(n1))

	var f1 float32 = -123.0000901
	var f2 float64 = -123.0000901
	f3 := -123.0000901
	var f4 = float32(-123.0000901) // always must convert type explicitly
	fmt.Println(f1, f2)
	fmt.Printf("f1 type is %T, size is %d\n", f1, unsafe.Sizeof(f1))
	fmt.Printf("f2 type is %T, size is %d\n", f2, unsafe.Sizeof(f2))
	fmt.Printf("f3 type is %T, size is %d\n", f3, unsafe.Sizeof(f3))
	fmt.Printf("f4 type is %T, size is %d\n", f4, unsafe.Sizeof(f4))

	var c1 complex64 = 5 + 10i
	fmt.Println(c1)
	fmt.Printf("c1 type is %T, size is %d\n", c1, unsafe.Sizeof(c1))

	var ch1 byte = 'a' // no char type, use byte instead
	var ch2 rune = '中'
	var ch3 = 'b'
	var ch4 = byte(ch2)
	fmt.Println(ch1, ch2, ch3, ch4)
	fmt.Printf("%c %c %c %c\n", ch1, ch2, ch3, ch4)
	fmt.Printf("ch3 type is %T, size is %d\n", ch3, unsafe.Sizeof(ch3))
	fmt.Printf("ch4 type is %T, size is %d\n", ch4, unsafe.Sizeof(ch4))

	// golang strings are immutable

	var s1 string = fmt.Sprintf("%s %d %f %t", "hello", 123, 1.3, true)
	var s2 string = strconv.Itoa(123) // FormatInt, FormatFloat, FormatBool, etc.
	fmt.Println(s1)
	fmt.Println(s2)

	var v1, e1 = strconv.ParseInt("hello", 10, 64) // ParseFloat, ParseBool, etc.
	var v2, e2 = strconv.ParseInt("123.1", 10, 64)
	var v3, e3 = strconv.ParseBool("yes")
	fmt.Println(v1, v2, v3)
	fmt.Println(v1, e1)
	fmt.Println(v2, e2)
	fmt.Println(v3, e3)
	fmt.Println(e1 == nil, e2 == nil, e3 == nil)
}

func DoConst() {
	// const can only be basic types
	//numa := 3
	//const PI float64 = 3.1415926
	//const b = numa + 3 // wrong, b must known at compile time

	const (
		a = iota // 0
		b        // 1
		c        // 2
	)
	fmt.Println(a, b, c)
}

func DoPtr() {
	var a int = 1
	var b *int = &a
	c := &a
	fmt.Println(a, b, *b, c, *c)
}

func DoAtithmetic() {
	var a int = 1
	a++
	// ++a // not allowed
	// b := a++ // not allowed
	fmt.Println(a)
}

func getb() byte {
	return 'b'
}

func DoCtrl() {
	var n1 int = 10
	var n2 int = 20
	var n3 int = 30
	var max int
	// must have parentheses
	if n1 > n2 {
		max = n1
	} else {
		max = n2
	}
	if n3 > max {
		max = n3
	}
	// will not compile
	/*
		if n1 = 10 {
			fmt.Println("n1 = 10")
		}
	*/
	fmt.Println(max)
	// switch: no need to add break
	// switch expression and case expression must be same type!!!
	var key byte = 'b'
	var a byte = 'a'
	switch key {
	case a, getb(), 'c', 'd', 'e':
		fmt.Println("Weekday")
		fallthrough // execute next case (1 case only, must be the last statement in case)
	case 'f', 'g':
		fmt.Println("Weekend")
	// case 'b': // duplicate case in switch is not allowed (variable ok )
	default:
		fmt.Println("Invalid")
	}
	// switch without expression
	var score int = 85
	var grade string
	// can also write: switch score := 85 {...}
	switch {
	case score >= 90:
		grade = "A"
	case score >= 80:
		grade = "B"
	case score >= 70:
		grade = "C"
	default:
		grade = "F"
	}
	fmt.Println(grade)

	var x interface{}
	var y = 10.0
	x = y
	switch i := x.(type) {
	case nil:
		fmt.Printf("x type is %T\n", i)
	case int:
		fmt.Printf("x type is int\n")
	case float64:
		fmt.Printf("x type is float64\n")
	case func(int) float64:
		fmt.Printf("x type is func(int)\n")
	case bool, string:
		fmt.Printf("x type is bool or string\n")
	default:
		fmt.Printf("unknown type\n")
	}
}

func DoInput() {
	var name string
	var age int

	fmt.Println("Please input your name and age:")
	fmt.Scanln(&name, &age)
	fmt.Printf("name: %s, age: %d\n", name, age)

	fmt.Println("Please input your name and age:")
	fmt.Scanf("%s %d", &name, &age)
	fmt.Printf("name: %s, age: %d\n", name, age)
}

func DoLoop() {
	var str string = "hello北京"
	var str2 []rune = []rune(str)
	for i := 0; i < len(str); i++ {
		fmt.Printf("%c\n", str[i])
	}
	j := 0
	for j < len(str2) {
		fmt.Printf("%c\n", str2[j])
		j++
	}
	k := 0
	// infinite loop : for ;; {}
	// do while loop
	for {
		fmt.Printf("%c\n", str[k])
		k++
		if k >= len(str) {
			break
		}
	}
	for i, val := range str {
		fmt.Printf("%d %c\n", i, val)
	}
	goto end
	fmt.Println("???")
end:
	fmt.Println("bye")
}

func Swap(a, b int) {
	a = a + b
	b = a - b
	a = a - b
	fmt.Println(a, b)
}

func init() {
	fmt.Println("I'am executed before main()!!")
}

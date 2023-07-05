package intro

import "fmt"

var id int = getId()

// name := "tom" // error: syntax error: non-declaration statement outside function body
// id = 3 // error: syntax error: non-declaration statement outside function body

var (
	id2      int = 2
	multFunc     = func(n1 int, n2 int) int {
		return n1 * n2
	}
)

func getId() int {
	fmt.Println("global varialble defined before main()!!!")
	return 1
}

func Calc(a, b float64, operator byte) float64 {
	switch operator {
	case '+':
		return a + b
	case '-':
		return a - b
	case '*':
		return a * b
	case '/':
		if b == 0 {
			panic("divided by zero")
		}
		return a / b
	}
	return 0
}

func Add(a *int, b int) {
	*a += b
}

func CalcSumSub(a, b int) (sum, sub int) {
	sum = a + b
	sub = a - b
	return
}

func DoCalc(funcVar func(int, int) (int, int), a, b int) (int, int) {
	return funcVar(a, b)
}

// variable parameters must be the last parameter
func PrintInts(ints ...int) {
	for i := 0; i < len(ints); i++ {
		fmt.Printf("%d ", ints[i])
	}
	fmt.Println()
}

// Think as a class
func AddUpper() func(int) int {
	var n int = 10
	return func(x int) int {
		n += x
		return n
	}
}

func DoFuncs() {

	// typedef
	type myInt int
	var a myInt = 10
	var b int = 20
	fmt.Println(a + myInt(b)) // must be converted

	type calcFuncType func(int, int) (int, int)

	res := Calc(2, 4, '+')
	fmt.Println(res)

	var funcVar func(float64, float64, byte) float64 = Calc
	res = funcVar(2.4, 4.8, '*')
	fmt.Println(res)

	var funcVar2 func(int, int) (int, int) = CalcSumSub
	sum, sub := DoCalc(funcVar2, 2, 4)
	fmt.Println(sum, sub)

	var funcVar3 calcFuncType = CalcSumSub
	sum, sub = DoCalc(funcVar3, 2, 4)
	fmt.Println(sum, sub)

	PrintInts(1, 6, 34, 6, 4)
}

func DoClosure() {
	f := AddUpper()
	fmt.Println(f(1))
	fmt.Println(f(2))
	fmt.Println(f(3))
}

func DoDefer() {
	// defer: execute after surrounding function returns
	// defer: LIFO
	// sequence: DoDefer -> defer 2 -> defer 1
	// use defer to close file, release resource, etc.
	n1 := 10
	n2 := 20
	defer fmt.Println("defer 1", n1) // n1, n2 copied
	defer fmt.Println("defer 2", n2)
	n1 += n2
	fmt.Println("DoDefer", n1, n2)
}

func DoLambda() {
	fun := func(a, b int) int {
		return a + b
	}
	fmt.Println(fun(1, 2))

	res := func(a, b int) int {
		return a + b
	}(1, 2)
	fmt.Println(res)

	res2 := multFunc(2, 3)
	fmt.Println(res2)
}

func init() {
	fmt.Println("Every package can have init() function, and because hello.go imports this package, this init() will be executed before global variable definition and main() in hello.go")
}

package proc

import "fmt"

type Cat struct {
	Name string
	Age  int
}

func DoChannel() {
	var intChan chan int = make(chan int, 3)

	fmt.Printf("ptr to chan: %v, channel address: %p\n", intChan, &intChan)

	intChan <- 10
	num := 211
	intChan <- num

	fmt.Printf("channel len: %d, cap: %d\n", len(intChan), cap(intChan))
	// if exceed cap, will cause deadlock

	var num2 int
	num2 = <-intChan
	fmt.Println("num2=", num2)

	// if no goroutine, will cause deadlock if no data in non-closed channel
	<-intChan // discard data
	/*
		num3 := <-intChan
		fmt.Println("num3=", num3)
	*/

	intChan <- -1
	// close channel
	close(intChan)

	//intChan <- 100 // panic: send on closed channel
	num4, ok := <-intChan // ok to read from closed channel
	fmt.Printf("num4=%d, ok=%v\n", num4, ok)
}

func DoAllChan() {
	var allChan chan interface{} = make(chan interface{}, 10)
	allChan <- Cat{"Tom", 10}
	allChan <- 10
	allChan <- "Tom"

	newCat := <-allChan
	fmt.Printf("newCat=%v, type=%T\n", newCat, newCat)
	// wrong, compiler still think newCat is interface{}
	//fmt.Printf("newCat.Name=%v, Age=\n", newCat.Name, newCat.Age)

	a := newCat.(Cat)
	fmt.Printf("newCat=%v, type=%T\n", a, a)
	fmt.Printf("newCat.Name=%v, Age=%v\n", a.Name, a.Age)

	v1 := <-allChan
	v2 := <-allChan
	fmt.Printf("v1=%v, v2=%v\n", v1, v2)
}

func DoChanTraversal() {
	var intChan chan int = make(chan int, 100)

	for i := 0; i < 100; i++ {
		intChan <- i * 2
	}

	// close channel
	close(intChan)

	// cannot use regular for loop
	for v := range intChan {
		fmt.Println("v=", v)
	}

	fmt.Printf("channel len: %d, cap: %d\n", len(intChan), cap(intChan))

	/*
		for {
			v, ok := <-intChan
			if !ok {
				break
			}
			fmt.Println("v=", v)
		}
	*/
}

func mysend(ch chan<- int, exitChan chan bool) {
	for i := 0; i < 10; i++ {
		ch <- i
	}
	close(ch)
	exitChan <- true
}

func myrecv(ch <-chan int, exitChan chan bool) {
	for {
		v, ok := <-ch
		if !ok {
			break
		}
		fmt.Println("v=", v)
	}
	exitChan <- true
}

func DoChanRW() {
	var chan2 chan<- int = make(chan int, 10) // write only
	chan2 <- 10
	//num := <-chan2 // error: invalid operation: <-chan2 (receive from send-only type chan<- int)

	//var chan3 <-chan int = make(chan int, 10) // read only
	//chan3 <- 10 // error: invalid operation: chan3 <- 10 (send to receive-only type <-chan int)

}

func DoChanSelect() {
	var chan1 chan int = make(chan int, 10)
	var chan2 chan string = make(chan string, 5)

	for i := 0; i < 10; i++ {
		chan1 <- i
	}

	for i := 0; i < 5; i++ {
		chan2 <- fmt.Sprintf("hello %d", i)
	}

	for {
		select {
		case v := <-chan1:
			fmt.Println("chan1 v=", v)
		case v := <-chan2:
			fmt.Println("chan2 v=", v)
		default:
			fmt.Println("no data")
			return
		}
	}
}

func sayHello() {
	for i := 0; i < 10; i++ {
		fmt.Println("hello world")
	}
}

func testPanic() {
	defer func() {
		if err := recover(); err != nil {
			fmt.Println("testPanic() recover err=", err)
		}
	}()

	var myMap map[int]string // nil map, cause panic
	myMap[0] = "golang"
}

func DoChanRevocer() {
	go sayHello()
	go testPanic()

	for i := 0; i < 10; i++ {
		fmt.Println("main() ok=", i)
	}
}

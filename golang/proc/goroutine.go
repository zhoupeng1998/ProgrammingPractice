package proc

// allow data race: "go run -race xxx.go"

import (
	"fmt"
	"runtime"
	"sync"
	"time"
)

var (
	amap = make(map[int]int, 10)
	lock sync.Mutex
)

func test() {
	for i := 1; i <= 10; i++ {
		fmt.Printf("test: %d\n", i)
		time.Sleep(time.Millisecond * 500)
	}
}

func DoGoroutine() {
	go test()
	for i := 1; i <= 10; i++ {
		fmt.Printf("main: %d\n", i)

		time.Sleep(time.Millisecond * 500)
	}
}

func DoCPU() {
	num := runtime.NumCPU()
	runtime.GOMAXPROCS(num)
	fmt.Println("CPU num: ", num)
}

func factorial(n int) int {
	var res = 1
	for i := 1; i <= n; i++ {
		res *= i
	}
	lock.Lock()
	amap[n] = res
	lock.Unlock()
	return res
}

func DoConcurrent() {
	for i := 1; i <= 20; i++ {
		go factorial(i)
	}
	//time.Sleep(time.Second * 3)
	runtime.Gosched()

	for i, v := range amap {
		fmt.Printf("amap[%d]=%d\n", i, v)
	}
}

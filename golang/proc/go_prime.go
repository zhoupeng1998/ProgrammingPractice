package proc

import "fmt"

func putNum(intChan chan int) {
	for i := 2; i < 8000; i++ {
		intChan <- i
	}
	close(intChan)
}

func primeNum(intChan chan int, primeChan chan int, exitChan chan bool) {
	for {
		num, ok := <-intChan
		if !ok {
			break
		}
		flag := true
		for i := 2; i < num; i++ {
			if num%i == 0 {
				flag = false
				break
			}
		}
		if flag {
			primeChan <- num
		}
	}
	exitChan <- true

}

func readPrime(primeChan chan int, exitChan chan bool) {
	for {
		num, ok := <-primeChan
		if !ok {
			break
		}
		fmt.Println("num=", num)
	}
	exitChan <- true
}

func DoGoPrime() {
	intChan := make(chan int, 1000)
	primeChan := make(chan int, 2000)
	exitChan := make(chan bool, 4)

	go putNum(intChan)
	for i := 0; i < 4; i++ {
		go primeNum(intChan, primeChan, exitChan)
	}
	go func() {
		for i := 0; i < 4; i++ {
			<-exitChan
		}
		close(primeChan)
	}()

	for {
		num, ok := <-primeChan
		if !ok {
			break
		}
		fmt.Println("num=", num)
	}

}

package proc

import (
	"fmt"
	"time"
)

func writeData(inchan chan int) {
	for i := 0; i < 50; i++ {
		inchan <- i
		fmt.Println("writing i=", i)
		time.Sleep(time.Millisecond * 250)
	}
	close(inchan)
}

func readData(inchan chan int, exitChan chan bool) {
	for {
		v, ok := <-inchan
		if !ok {
			break
		}
		fmt.Println("reading v=", v)
	}
	exitChan <- true
	close(exitChan)
}

func DoChanExample() {

	inChan := make(chan int, 50)
	exitChan := make(chan bool, 1)

	go writeData(inChan)
	go readData(inChan, exitChan)

	/*
		for {
			_, ok := <-exitChan
			if !ok {
				break
			}
		}
	*/
	<-exitChan

}

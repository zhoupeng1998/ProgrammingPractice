package intro

import (
	"errors"
	"fmt"
)

func test() {
	defer func() {
		if err := recover(); err != nil {
			fmt.Println("err = ", err)
		}
	}()
	num1 := 10
	num2 := 0
	res := num1 / num2
	fmt.Println(res)
}

func readConf(name string) (err error) {
	if name == "config.ini" {
		return nil
	} else {
		return errors.New("read config.ini error")
	}
}

func test2() {
	err := readConf("config2.ini")
	if err != nil {
		panic(err)
	}
	fmt.Println("test2() after readConf()")
}

func DoErr() {
	//test()
	test2()
	fmt.Println("code after test()")
}

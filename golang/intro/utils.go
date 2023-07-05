package intro

import (
	"fmt"
	"strconv"
	"strings"
	"time"
)

func DoStr() {
	str := "hello北京"
	fmt.Println(len(str))

	r := []rune(str)
	fmt.Println(len(r))

	n, err := strconv.Atoi("123")
	fmt.Println(n, err)

	str = strconv.Itoa(123)
	fmt.Println(str)

	bytes := []byte("hello go")
	fmt.Println(bytes)
	fmt.Printf("%v\n", bytes)

	str = string([]byte{97, 98, 99})
	fmt.Println(str)

	str = strconv.FormatInt(123, 2)
	fmt.Println(str)
	str = strconv.FormatInt(123, 16)
	fmt.Println(str)

	fmt.Println(strings.Contains("hello", "ll"))
	fmt.Println(strings.Index("hello", "ll"))
	fmt.Println(strings.Count("hello", "l"))
	fmt.Println(strings.EqualFold("hello", "HELLO"))
	fmt.Println(strings.Replace("hello", "l", "Lo", 2)) // -1 for all
	fmt.Println(strings.Split("hello,world", ","))
	fmt.Println(strings.ToLower("HELLO"))
	fmt.Println(strings.ToUpper("hello"))
	fmt.Println(strings.TrimSpace(" hello "))
	fmt.Println(strings.Trim(" hello ", "o "))
	fmt.Println(strings.TrimLeft(" hello ", " h"))
	fmt.Println(strings.TrimRight(" hello ", "o "))
	fmt.Println(strings.HasPrefix("ftp://192.168.0.1", "ftp"))
	fmt.Println(strings.HasSuffix("mypic.jpg", "jpg"))
}

func DoDateTime() {
	now := time.Now()
	fmt.Printf("now is %v, type %T\n", now, now)
	fmt.Println(now.Year(), now.Month(), now.Weekday(), now.Day(), now.Hour(), now.Minute(), now.Second(), now.Nanosecond())
	fmt.Println(now.Unix(), now.UnixNano())
	fmt.Println(int(now.Month()), int(now.Weekday()))

	dateStr := fmt.Sprintf("now is %d-%d-%d %d:%d:%d", now.Year(), now.Month(), now.Day(), now.Hour(), now.Minute(), now.Second())
	fmt.Println(dateStr)

	// must be 2006-01-02 15:04:05
	fmt.Println(now.Format("2006_01-02 15:04:05"))
	fmt.Println(now.Format("2006-01-02 15:04:05.000"))
	fmt.Println(now.Format("2006.01.02 15:04:05.000 Mon Jan"))
	fmt.Println(now.Format("2006-01-02"))
	fmt.Println(now.Format("15:04:05"))

	fmt.Println("start sleep")
	time.Sleep(100 * 5 * time.Millisecond)
	fmt.Println("end sleep")

	fmt.Println(time.Now().UnixNano()-now.UnixNano(), "ns passed")
}

func DoNew() {
	num1 := 123
	fmt.Printf("%T %v %v\n", num1, num1, &num1)

	// new() return pointer
	num2 := new(int)
	*num2 = 123
	fmt.Printf("%T %v %v\n", num2, num2, *num2)
}

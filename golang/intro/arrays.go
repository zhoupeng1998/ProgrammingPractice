package intro

import "fmt"

// must specify length of array because it is part of array type
// [3]int and [4]int are different types
// arrays passed by value
func doArrayParam(arr [3]int) {
	arr[0] = 88
	arr[1] = 99
	arr[2] = 100
}

func doArrayParam2(arr *[3]int) {
	(*arr)[0] = 88
	(*arr)[1] = 99
	(*arr)[2] = 100
}

func DoArray() {
	var hens [6]float64
	hens[0] = 3.0
	hens[1] = 4.0
	hens[2] = 5.0
	hens[3] = 6.0
	hens[4] = 7.0
	hens[5] = 8.0
	var sum float64 = 0.0
	for i := 0; i < len(hens); i++ {
		sum += hens[i]
	}
	fmt.Printf("sum = %v, avg = %v\n", sum, sum/float64(len(hens)))
	fmt.Println(&hens[0], &hens[1], &hens[2])

	/*
		fmt.Printf("Enter values for hens:\n")
		for i := 0; i < len(hens); i++ {
			fmt.Scanln(&hens[i])
		}
		fmt.Println(hens)
	*/

	var arr1 [3]int = [3]int{1, 2, 3}
	var arr2 = [3]int{1, 2, 3}
	var arr3 = [...]int{1, 2, 3}
	var names = [...]string{1: "Tom", 0: "Jack", 3: "Mary"}
	fmt.Println(arr1)
	fmt.Println(arr2)
	fmt.Println(arr3)
	fmt.Println(names, len(names))
	fmt.Printf("%T\n", names)

	for i, v := range names {
		fmt.Printf("names[%d] = %v\n", i, v)
	}
	for i := range names {
		fmt.Printf("names[%d] = %v\n", i, names[i])
	}

	doArrayParam(arr1)
	doArrayParam2(&arr1)
	fmt.Println(arr1)

	for i, j := 0, len(arr1)-1; i < j; i, j = i+1, j-1 {
		arr1[i], arr1[j] = arr1[j], arr1[i]
	}
	fmt.Println(arr1)
}

func doSliceParam(slice []int) {
	slice[0] = 888
	slice = append(slice, 999) // it will not change the original slice
}

func DoSlice() {
	var intArr [5]int = [...]int{1, 5, 3, 8, 6}
	slice := intArr[1:3]
	fmt.Println(slice)
	fmt.Printf("type = %T, len = %v, cap = %v\n", slice, len(slice), cap(slice))
	fmt.Println(&intArr[1], &slice[0])
	fmt.Printf("%p %p\n", &intArr, &slice)
	slice[1] = 44
	fmt.Println(intArr)
	slice = append(slice, 55)
	slice = append(slice, 66, 77)
	fmt.Println(slice, intArr)
	fmt.Printf("type = %T, len = %v, cap = %v\n", slice, len(slice), cap(slice))

	var slice2 []int = make([]int, 4, 10) // make(type, len, [cap]), cap defaults to len, cap must be >= len otherwise error
	fmt.Println(slice2, len(slice2), cap(slice2))

	var slice3 []int = make([]int, 3)
	fmt.Println(slice3, len(slice3), cap(slice3))

	var slice4 []int = []int{1, 2, 3}
	fmt.Println(slice4, len(slice4), cap(slice4))

	var arr5 []int = []int{1, 2, 3, 4, 5}
	var slice5 []int = make([]int, 1)
	copy(slice5, arr5)
	fmt.Println(slice5, len(slice5), cap(slice5))

	doSliceParam(slice5)
	fmt.Println(slice5, len(slice5), cap(slice5))

	str := "hello@123abc"
	slice6 := str[6:]
	fmt.Printf("%T, %v\n", slice6, slice6)

	fmt.Println([]rune(str))
}

func Do2DArray() {
	var arr [4][6]int
	arr[1][2] = 1
	arr[2][1] = 2
	arr[2][3] = 3
	for i := 0; i < len(arr); i++ {
		for j := 0; j < len(arr[i]); j++ {
			fmt.Printf("%v ", arr[i][j])
		}
		fmt.Println()
	}
	fmt.Printf("%p\n", &arr)
	fmt.Printf("%p\n", &arr[0])
	fmt.Printf("%p\n", &arr[1])

	var sli [][]int = make([][]int, 6)
	for i := 0; i < len(sli); i++ {
		sli[i] = make([]int, i+1)
		for j := 0; j < len(sli[i]); j++ {
			sli[i][j] = i + j
		}
	}
	fmt.Println(sli)
	fmt.Printf("%p\n", &sli)
	fmt.Printf("%p\n", &sli[0])
	fmt.Printf("%p\n", &sli[0][0])
	fmt.Printf("%p\n", &sli[1])

	for i, v := range sli {
		for j, v2 := range v {
			fmt.Printf("sli[%d][%d] = %v\n", i, j, v2)
		}
	}
}

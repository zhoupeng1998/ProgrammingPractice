package intro

import "fmt"

func bubbleSort(arr []int) {
	for i := 0; i < len(arr)-1; i++ {
		for j := 0; j < len(arr)-1-i; j++ {
			if arr[j] > arr[j+1] {
				arr[j], arr[j+1] = arr[j+1], arr[j] // swap
			}
		}
	}
}

func DoBubbleSort() {
	var arr []int = []int{24, 69, 80, 57, 13}
	bubbleSort(arr)
	fmt.Println(arr)
}

func binarySearch(arr []int, target int) int {
	var begin, end, mid int = 0, len(arr) - 1, 0
	for begin < end {
		mid = begin + (end-begin)/2
		if arr[mid] < target {
			begin = mid + 1
		} else {
			end = mid
		}
	}
	if arr[begin] == target {
		return begin
	} else {
		return -1
	}
}

func binarySearchRight(arr []int, target int) int {
	var begin, end, mid int = 0, len(arr) - 1, 0
	for begin < end {
		mid = begin + (end-begin+1)/2
		if arr[mid] <= target {
			begin = mid
		} else {
			end = mid - 1
		}
	}
	if arr[begin] == target {
		return begin
	} else {
		return -1
	}
}

func DoBinarySearch() {
	var arr []int = []int{1, 8, 10, 89, 1000, 1000, 1234}
	var index int = binarySearch(arr, 1000)
	var index2 int = binarySearchRight(arr, 1000)
	fmt.Println(index, index2)
}

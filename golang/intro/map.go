package intro

import (
	"fmt"
	"sort"
)

func doMapParam(amap map[string]string) {
	amap["90"] = "100"
}

func DoMap() {
	var amap map[string]string = make(map[string]string)
	amap["name"] = "tom"
	amap["age"] = "18"
	amap["address"] = "beijing"
	fmt.Println(amap)

	var bmap map[string]map[string]string = make(map[string]map[string]string)
	bmap["stu1"] = make(map[string]string)
	bmap["stu1"]["name"] = "tom"
	bmap["stu1"]["age"] = "18"
	bmap["stu2"] = make(map[string]string)
	bmap["stu2"]["name"] = "jerry"
	bmap["stu2"]["age"] = "20"
	bmap["stu3"] = amap
	bmap["stu3"]["name"] = "jack"
	fmt.Println(bmap)
	fmt.Println(amap)

	var cmap = map[string]string{
		"name": "tom",
		"age":  "18",
	}
	doMapParam(cmap)
	fmt.Println(cmap)
}

func DoMapCRUD() {
	amap := map[string]string{
		"name": "tom",
		"age":  "18",
		"addr": "beijing",
	}

	// add
	amap["hobby"] = "basketball"

	// update
	amap["name"] = "jack"

	// delete
	delete(amap, "age")

	fmt.Println(amap)

	// search
	val, ok := amap["age"]
	fmt.Println(val, ok)
	val = amap["name"]
	fmt.Println(val)

	for key, val := range amap {
		fmt.Println(key, val)
	}
}

func DoMapSlice() {
	var mapslice []map[string]string = make([]map[string]string, 2)
	if mapslice[0] == nil {
		mapslice[0] = make(map[string]string)
		mapslice[0]["name"] = "tom"
		mapslice[0]["age"] = "18"
		mapslice[0]["address"] = "beijing"
	}
	if mapslice[1] == nil {
		mapslice[1] = make(map[string]string)
		mapslice[1]["name"] = "jerry"
		mapslice[1]["age"] = "20"
		mapslice[1]["address"] = "shanghai"
	}
	mapslice = append(mapslice, map[string]string{"name": "jack", "age": "22", "address": "guangzhou"})
	fmt.Println(mapslice)
}

func DoMapSort() {
	amap := map[int]int{
		10: 100,
		1:  10,
		4:  40,
		2:  20,
		3:  30,
	}
	fmt.Println(amap)

	keys := make([]int, 0, len(amap))
	for key, _ := range amap {
		keys = append(keys, key)
	}
	sort.Ints(keys)
	fmt.Println(keys)
	for _, key := range keys {
		fmt.Println(key, amap[key])
	}
}

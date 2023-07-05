package files

import (
	"encoding/json"
	"fmt"
)

type Person struct {
	Name string `json:"name"`
	Age  int    `json:"age"`
	Addr string `json:"address"`
}

func DoJsonStructSerialize() string {
	person := Person{
		Name: "Jack",
		Age:  18,
		Addr: "Beijing",
	}
	data, err := json.Marshal(&person)
	if err != nil {
		fmt.Println("json marshal err:", err)
	}
	fmt.Println("json str:", string(data))
	return string(data)
}

func DoJsonMapSerialize() string {
	var a map[string]interface{} = make(map[string]interface{})
	a["name"] = "Candy"
	a["age"] = 10
	a["address"] = "Shanghai"
	data, err := json.Marshal(a)
	if err != nil {
		fmt.Println("json marshal err:", err)
	}
	fmt.Println("json str:", string(data))
	return string(data)
}

func DoJsonSliceSerialize() string {
	var slice []map[string]interface{} = make([]map[string]interface{}, 0)
	var m1 map[string]interface{} = make(map[string]interface{})
	m1["name"] = "Candy"
	m1["age"] = 10
	m1["address"] = "Shanghai"
	slice = append(slice, m1)
	var m2 map[string]interface{} = make(map[string]interface{})
	m2["name"] = "Jack"
	m2["age"] = 30
	m2["address"] = "Beijing"
	slice = append(slice, m2)
	data, err := json.Marshal(slice)
	if err != nil {
		fmt.Println("json marshal err:", err)
	}
	fmt.Println("json str:", string(data))
	return string(data)
}

func DoJsonStructDeserialize(jsonStr string) {
	var person Person
	err := json.Unmarshal([]byte(jsonStr), &person)
	if err != nil {
		fmt.Println("json unmarshal err:", err)
	}
	fmt.Println("json struct:", person)
}

func DoJsonMapDeserialize(jsonStr string) {
	var a map[string]interface{}
	err := json.Unmarshal([]byte(jsonStr), &a)
	if err != nil {
		fmt.Println("json unmarshal err:", err)
	}
	fmt.Println("json map:", a)
}

func DoJsonSliceDeserialize(jsonStr string) {
	var slice []map[string]interface{}
	err := json.Unmarshal([]byte(jsonStr), &slice)
	if err != nil {
		fmt.Println("json unmarshal err:", err)
	}
	fmt.Println("json slice:", slice)
}

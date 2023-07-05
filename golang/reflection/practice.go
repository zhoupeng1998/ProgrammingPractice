package reflection

import (
	"fmt"
	"reflect"
)

func reflectFloat(b interface{}) {
	rType := reflect.TypeOf(b)
	rVal := reflect.ValueOf(b)
	rType = rVal.Type()

	iV := rVal.Interface()
	fV := iV.(*float64)

	fmt.Printf("rType: %T %v\n", rType, rType)
	fmt.Printf("fV: %T %v\n", fV, *fV)

	rVal.Elem().SetFloat(3.4)
}

func DoReflectPractice() {
	var v float64 = 1.2
	reflectFloat(&v)
	fmt.Println("v=", v)
}

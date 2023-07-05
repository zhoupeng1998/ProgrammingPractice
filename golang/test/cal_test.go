// must named as "xxx_test.go"
// run with "go test -v"
// test single file: "go test -v cal_test.go"
// test single function: "go test -v -run TestAddUpper"

package main

import (
	"testing"

	"./unittest"
)

func TestAddUpper1(t *testing.T) {
	res := unittest.AddUpper(10)
	if res != 55 {
		t.Fatalf("AddUpper(10) error, expected:%v, actual:%v", 55, res)
	}
	t.Logf("AddUpper(10) success, expected:%v, actual:%v", 55, res)
}

func TestAddUpper2(t *testing.T) {
	res := unittest.AddUpper(10)
	if res != 54 {
		t.Fatalf("AddUpper(10) error, expected:%v, actual:%v", 55, res)
	}
	t.Logf("AddUpper(10) success, expected:%v, actual:%v", 55, res)
}

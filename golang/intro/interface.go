package intro

import "fmt"

type T interface {
}

// no variable, no constructor, no method
type Usb interface {
	Start()
	Stop()
}

// can inherit from interface
type Usb2 interface {
	Usb
	Pause()
}

type Phone struct {
	Name string
}

func (p *Phone) Start() {
	fmt.Println(p.Name, "phone is starting")
}

func (p *Phone) Stop() {
	fmt.Println(p.Name, "phone is stopping")
}

func (p *Phone) Call() {
	fmt.Println(p.Name, "phone is calling")
}

type Camera struct {
	Name string
}

func (c *Camera) Start() {
	fmt.Println(c.Name, "camera is starting")
}

func (c *Camera) Stop() {
	fmt.Println(c.Name, "camera is stopping")
}

func (c *Camera) Pause() {
	fmt.Println(c.Name, "camera is pausing")
}

type Computer struct {
}

func (c *Computer) Working(usb Usb) {
	usb.Start()
	phone, ok := usb.(*Phone)
	if ok {
		fmt.Println("It is a phone, calling...")
		phone.Call()
	}
	usb.Stop()
}

func (c *Computer) Working2(usb Usb2) {
	usb.Start()
	usb.Stop()
	usb.Pause()
}

// integer is not a struct, but it can also implement interface
type integer int

func (i integer) Start() {
	fmt.Println("int is starting", i)
}

func (i integer) Stop() {
	fmt.Println("int is stopping", i)
}

func DoInterface() {
	// polymorphism only works on interface
	var phone Usb = new(Phone)
	phone.Start()
	phone.Stop()

	var camera Usb = new(Camera)
	camera.Start()
	camera.Stop()

	c := new(Computer)
	c.Working(phone)
	c.Working(camera)

	var i integer = 10
	c.Working(i)

	// assigning empty interface to any type
	var t T = 6
	var t2 interface{} = c
	fmt.Printf("%T %v, %T %v\n", t, t, t2, t2)
	var a int = 10 + t.(int)
	fmt.Println(a)
	t2.(*Computer).Working(phone)

	var phone2 Phone = Phone{"iPhone"}
	//var u Usb = phone // *Phone implements Usb, but Phone does not
	var u Usb = &phone2 // correct
	u.Start()

	var usbArr []Usb = make([]Usb, 2)
	usbArr[0] = phone
	usbArr[1] = camera
	fmt.Println(usbArr)

	// type assertion
	var myphone Usb = new(Phone)
	myphone, ok := myphone.(*Phone)
	fmt.Println(myphone, ok)
	myphone, ok = myphone.(*Camera)
	fmt.Println(myphone, ok)
}

func DoTypeAssertion(items ...interface{}) {
	for i, x := range items {
		switch x.(type) {
		case bool:
			fmt.Printf("param #%d is a bool\n", i)
		case int, int8, int16, int32, int64:
			fmt.Printf("param #%d is an int\n", i)
		case uint, uint8, uint16, uint32, uint64:
			fmt.Printf("param #%d is an uint\n", i)
		case float32, float64:
			fmt.Printf("param #%d is a float\n", i)
		case complex64, complex128:
			fmt.Printf("param #%d is a complex\n", i)
		case string:
			fmt.Printf("param #%d is a string\n", i)
		default:
			fmt.Printf("param #%d is something else\n", i)
		}
	}
}

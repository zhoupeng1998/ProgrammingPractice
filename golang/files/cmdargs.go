package files

import (
	"flag"
	"fmt"
	"os"
)

func DoCmdArgs() {
	fmt.Println(len(os.Args), " args")
	for i, v := range os.Args {
		fmt.Printf("args[%d]=%s\n", i, v)
	}
}

func DoFlagArgs() {
	var usr string
	var pwd string
	var host string
	var port int

	flag.StringVar(&usr, "u", "", "username")
	flag.StringVar(&pwd, "pwd", "", "password")
	flag.StringVar(&host, "h", "localhost", "host")
	flag.IntVar(&port, "p", 3306, "port")

	flag.Parse()
	fmt.Printf("usr=%s, pwd=%s, host=%s, port=%d\n", usr, pwd, host, port)
}

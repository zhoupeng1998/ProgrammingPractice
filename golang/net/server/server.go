package main

import (
	"fmt"
	"io"
	"net"
)

func process(conn net.Conn) {
	defer conn.Close()

	buf := make([]byte, 1024)
	for {
		n, err := conn.Read(buf)
		if err == io.EOF {
			fmt.Println("Client closed:", conn.RemoteAddr().String())
			return
		} else if err != nil {
			fmt.Println("Read error:", err)
			return
		}
		fmt.Printf("Read from %v: %v\n", conn.RemoteAddr().String(), string(buf[:n]))
	}
}

func main() {
	fmt.Println("Star listening on port 8888")
	listen, err := net.Listen("tcp", "localhost:8888") // 0.0.0.0 also ok
	if err != nil {
		fmt.Println("Listen error:", err)
		return
	}
	defer listen.Close()
	fmt.Printf("Waiting for clients: %v\n", listen.Addr())

	for {
		conn, err := listen.Accept()
		if err != nil {
			fmt.Println("Accept error:", err)
			return
		}
		fmt.Printf("Accept %v %v\n", conn, conn.RemoteAddr().String())
		go process(conn)
	}
}

package main

import (
	"bufio"
	"net"
	"os"
	"strings"
)

func main() {
	conn, err := net.Dial("tcp", "localhost:8888")
	if err != nil {
		panic(err)
	}
	defer conn.Close()

	reader := bufio.NewReader(os.Stdin)

	for {
		line, err := reader.ReadString('\n')
		line = strings.Trim(line, "\r\n")
		if line == "exit" {
			break
		}
		if err != nil {
			panic(err)
		}

		conn.Write([]byte(line))
	}
}

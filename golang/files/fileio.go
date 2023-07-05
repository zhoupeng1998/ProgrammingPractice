package files

import (
	"bufio"
	"fmt"
	"io"
	"io/ioutil"
	"os"
)

func DoReadFile() {
	file, err := os.Open("inputfile.txt")
	if err != nil {
		fmt.Println("Open file error", err)
		return
	}
	fmt.Println(file, err)

	// read file by lines
	reader := bufio.NewReader(file)
	for {
		str, err := reader.ReadString('\n')
		fmt.Print(str)
		if err == io.EOF {
			fmt.Println()
			break
		}
	}

	// read entire file (not opening/closing file, hidden by ioutil.ReadFile)
	content, err := ioutil.ReadFile("inputfile.txt")
	if err != nil {
		fmt.Println("Read file error", err)
	} else {
		fmt.Printf("%T\n %s\n", content, content)
	}

	err = file.Close()
	if err != nil {
		fmt.Println("Close file error", err)
		return
	}
}

func DoWriteFile() {
	// O_APPEND: append to file, O_TRUNC: clear file, O_RDWR: read and write
	file, err := os.OpenFile("outputfile.txt", os.O_CREATE|os.O_WRONLY, 0666)
	if err != nil {
		fmt.Println("Open file error", err)
		return
	}
	defer file.Close()

	writer := bufio.NewWriter(file)
	for i := 0; i < 10; i++ {
		writer.WriteString("bye world\n")
	}
	// writer is buffered, so need to flush to file
	writer.Flush()

	err = file.Close()
	if err != nil {
		fmt.Println("Close file error", err)
		return
	}
}

func PathExists(path string) (bool, error) {
	_, err := os.Stat(path)
	if err == nil {
		return true, nil // file exists
	} else if os.IsNotExist(err) {
		return false, nil // file does not exist
	} else {
		return false, err // error, not sure if file exists
	}
}

func DoCheckFileExists() {
	exists, err := PathExists("inputfile.txt")
	if err != nil {
		fmt.Println("Check file error", err)
		return
	}
	fmt.Println("inputfile exists:", exists)
	exists, err = PathExists("outputfile.txt")
	if err != nil {
		fmt.Println("Check file error", err)
		return
	}
	fmt.Println("outputfile exists:", exists)
}

func CopyFile(dstPath, srcPath string) (written int64, err error) {
	srcFile, err := os.Open(srcPath)
	if err != nil {
		fmt.Println("Open file error", err)
		return
	}
	defer srcFile.Close()

	dstFile, err := os.OpenFile(dstPath, os.O_CREATE|os.O_WRONLY, 0666) // FileMode only useful in Linux
	if err != nil {
		fmt.Println("Open file error", err)
		return
	}
	defer dstFile.Close()

	writer := bufio.NewWriter(dstFile)
	return io.Copy(writer, srcFile)
}

func DoCopyFile() {
	srcFile := "inputfile.txt"
	dstFile := "copiedfile.txt"

	written, err := CopyFile(dstFile, srcFile)
	if err != nil {
		fmt.Println("Copy file error", err)
		return
	}
	fmt.Printf("Copied %d bytes.\n", written)
	//io.Copy()
	// TODO
}

type ChStat struct {
	CharCount  int
	NumCount   int
	SpaceCount int
	OtherCount int
}

func DoCharStat() {
	fileName := "inputfile.txt"
	file, err := os.Open(fileName)
	if err != nil {
		fmt.Println("Open file error", err)
		return
	}
	defer file.Close()

	var chStat ChStat
	reader := bufio.NewReader(file)
	for {
		str, err := reader.ReadString('\n')
		if err == io.EOF {
			break
		}
		for _, ch := range str {
			switch {
			case ch >= 'a' && ch <= 'z':
				fallthrough
			case ch >= 'A' && ch <= 'Z':
				chStat.CharCount++
			case ch >= '0' && ch <= '9':
				chStat.NumCount++
			case ch == ' ' || ch == '\t':
				chStat.SpaceCount++
			default:
				chStat.OtherCount++
			}
		}
	}
	fmt.Printf("CharCount=%d, NumCount=%d, SpaceCount=%d, OtherCount=%d\n", chStat.CharCount, chStat.NumCount, chStat.SpaceCount, chStat.OtherCount)
}

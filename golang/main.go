// command: go run main.go
// compile at gohome: go build -o <exe>/<path> /<path>/<to>/<main>/<package>/<directory>

package main

import (
	"fmt"
	"math/rand"
	"os"
	"time"

	_ "./files"
	_ "./intro"
	"./other"
	_ "./proc"
	_ "./reflection"
	// import package from local directory
	// st "./intro" // alias, can be used as st.Calc() but cannot be used as intro.Calc()
	// try "go env -w GO111MODULE=off".
)

func init() {
	rand.Seed(time.Now().UnixNano())
}

func GetArgs() {
	fmt.Println(len(os.Args), " args")
	for i, v := range os.Args {
		fmt.Printf("args[%d]=%s\n", i, v)
	}
}

func main() {
	//GetArgs()

	//intro.DoVar()
	//intro.DoPtr()
	//fmt.Println(model.ModelName)
	//intro.DoInput()
	//intro.DoCtrl()
	//intro.DoVar()
	//intro.DoConst()
	//intro.DoLoop()
	//intro.DoFuncs()
	//intro.DoLambda()
	//intro.DoClosure()
	//intro.DoDefer()
	//intro.DoStr()
	//intro.DoDateTime()
	//intro.DoNew()
	//intro.DoErr()
	//intro.DoArray()
	//intro.DoSlice()
	//intro.DoBubbleSort()
	//intro.DoBinarySearch()
	//intro.Do2DArray()
	//intro.DoMap()
	//intro.DoMapCRUD()
	//intro.DoMapSlice()
	//intro.DoMapSort()
	//intro.DoStruct()
	//intro.DoStructMem()
	//intro.DoSerialize()
	//aperson := intro.NewPerson("Tom", 20, 10000)
	//aperson.SetAge(22)
	//fmt.Println(aperson.GetName(), aperson.GetAge(), aperson.GetSalary())
	//intro.DoInheritance()
	//intro.DoInterface()
	//intro.DoTypeAssertion(2.2, 444, -1223, uint64(888), "hello", false)
	//files.DoReadFile()
	//files.DoWriteFile()
	//files.DoCheckFileExists()
	//files.DoCopyFile()
	//files.DoCharStat()
	//files.DoCmdArgs()
	//files.DoFlagArgs()
	/*
		JsonStruct := files.DoJsonStructSerialize()
		JsonFiles := files.DoJsonMapSerialize()
		JsonSlice := files.DoJsonSliceSerialize()
		files.DoJsonStructDeserialize(JsonStruct)
		files.DoJsonMapDeserialize(JsonFiles)
		files.DoJsonSliceDeserialize(JsonSlice)
	*/
	//proc.DoGoroutine()
	//proc.DoCPU()
	//proc.DoConcurrent()
	//proc.DoChannel()
	//proc.DoAllChan()
	//proc.DoChanTraversal()
	//proc.DoChanExample()
	//proc.DoChanSelect()
	//proc.DoGoPrime()
	//proc.DoChanRevocer()
	//reflection.DoReflect()
	//reflection.DoReflectKind()
	//reflection.DoReflectSet()
	//reflection.DoReflectPractice()
	//reflection.DoReflectExample()
	//testredis.DoRedis()
	other.DoHash()
}

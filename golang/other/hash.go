package other

import (
	"crypto/sha256"
	"encoding/hex"
	"fmt"
)

func DoHash() {
	message := "hello world"

	hash := sha256.New()

	byteMsg := []byte(message)
	fmt.Println(len(byteMsg))

	hash.Write(byteMsg)

	hashValue := hash.Sum(nil)
	fmt.Printf("%T %v %x\n", hashValue, len(hashValue), hashValue)

	hashString := hex.EncodeToString(hashValue)

	fmt.Println(hashString)
}

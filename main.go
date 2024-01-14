package main

// #include <stdlib.h>
// #include "cpu-info/processor.h"
import "C"
import (
	"fmt"
	"runtime"
)

func main() {

	if isDarwin() {
		fmt.Println("running Darwin")
	} else {
		fmt.Println("not running Darwin")
	}
	if isX86() {
		fmt.Println("running x86 arch")
		return
	}
	fmt.Println("not running x86 arch")

	Processor := C._get_proc_info()
	fmt.Printf("ID: %d\n", C.int(Processor.ID))

}

func isDarwin() bool {
	if runtime.GOOS == "darwin" {
		return true
	}
	return false

}

func isX86() bool {
	if runtime.GOARCH == "amd64" || runtime.GOARCH == "Amd64p32" {
		return true
	}
	return false

}

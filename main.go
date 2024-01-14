package main

// #cgo LDFLAGS: -L. -lprocessor
// #include <stdlib.h>
// #include "cpu-info/processor.h"
import "C"
import (
	"fmt"
	"runtime"
	"strings"
)

func main() {

	checkOS()
	var proc Processor
	proc.get_info()

}

func checkOS() {
	if runtime.GOOS == "darwin" {
		fmt.Printf("running Darwin, ")
	} else {
		fmt.Printf("not running Darwin, ")
	}
	if runtime.GOARCH == "amd64" || runtime.GOARCH == "Amd64p32" {
		fmt.Println("running x86 arch")

	} else {
		fmt.Println("not running x86 arch")
	}
}

func (proc *Processor) get_info() {
	p := C.get_proc_info()
	proc.ID = int(C.int(p.ID))
	proc.Model = int(C.int(p.Model))
	proc.NumCores = uint32(C.uint(p.NumCores))
	proc.NumThreads = uint32(C.uint(p.NumThreads))
	proc.Vendor = C.GoString(p.Vendor)
	proc.Capabilities = []string(strings.Split(C.GoString(p.Capabilites), " "))

}

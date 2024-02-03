package main

// #cgo LDFLAGS: -L. -lprocessor
import "C"
import (
	"fmt"
	"runtime"

	"github.com/j0rdan0/sysinfo/pkg/cpu"
)

func main() {

	proc := new(cpu.Processor)
	proc.Cores = make([]*cpu.ProcessorCore, 0)
	proc.Get_proc_info()
	fmt.Println(proc)

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

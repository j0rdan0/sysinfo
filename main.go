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

	C.test_hwloc()
	checkOS()
	var proc Processor
	var core ProcessorCore
	proc.get_proc_info()
	core.get_core_info()
	fmt.Println(proc.String())
	fmt.Println(core.String())

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

func (proc *Processor) get_proc_info() {
	p := C.get_proc_info()
	proc.ID = int(C.int(p.ID))
	proc.Model = int(C.int(p.Model))
	proc.NumCores = uint32(C.uint(p.NumCores))
	proc.NumThreads = uint32(C.uint(p.NumThreads))
	proc.Vendor = C.GoString(p.Vendor)
	proc.Capabilities = []string(strings.Split(C.GoString(p.Capabilites), " "))
}

func (proc *Processor) String() string {

	features := strings.Join(proc.Capabilities, " ")
	return fmt.Sprintf("Processor ID: %d Model: %d Physical cores: %d Hardware threads: %d Vendor: %s Features: %s", proc.ID, proc.Model, proc.NumCores, proc.NumThreads, proc.Vendor, features)
}

func (core *ProcessorCore) get_core_info() {
	c := C.get_core_info()
	core.ID = int(C.int(c.ID))
	core.NumThreads = uint32(C.uint(c.NumThreads))
}

func (core *ProcessorCore) String() string {
	return fmt.Sprintf("Core ID: %d Core Num threads: %d\n", core.ID, core.NumThreads)
}

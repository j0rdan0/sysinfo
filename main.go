package main

// #cgo LDFLAGS: -L. -lprocessor
// #include <stdlib.h>
// #include "cpu-info/processor.h"
import "C"
import (
	"fmt"
	"os"
	"runtime"
	"strconv"
	"unsafe"
)

func main() {

	checkOS()

	proc := new(Processor)
	proc.get_proc_info()
	fmt.Println(proc.String())
	for _, core := range proc.Cores {
		fmt.Println(core.ID)
	}
	core := new(ProcessorCore)
	index, err := strconv.Atoi(os.Args[1])
	if err != nil {
		fmt.Printf("usage: %s <index>\n", os.Args[0])
		return
	}
	core.get_core_info(index)
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
	proc.ID = int(p.ID)
	proc.NumCores = uint32(p.NumCores)
	proc.NumThreads = uint32(p.NumThreads)
	proc.Model = int(p.Model)
	proc.Vendor = C.GoString(p.Vendor)
	proc.Capabilites = C.GoString(p.Capabilites)
	core := new(ProcessorCore)
	for i := 0; i < int(p.NumCores); i++ {
		core.get_core_info(i)
		proc.Cores = append(proc.Cores, core)
	}

}

func (core *ProcessorCore) get_core_info(i int) {

	c := C.ProcessorCore{}
	size := C.size_t(unsafe.Sizeof(c)) // get size to know how much to allocate for it in next step

	core_struct := C.malloc(size)
	defer C.free(core_struct)
	threads := 2                                                               // harcoded for the moment
	C.get_core_info((*C.ProcessorCore)(core_struct), C.int(i), C.int(threads)) // get core info

	data := (*C.ProcessorCore)(unsafe.Pointer(core_struct))
	defer C.free(unsafe.Pointer(data.LogicalProcessors))

	// this is needed to change int* type to []C.int in Golang
	logicalProcessors := make([]C.int, int(data.NumThreads))
	C.memcpy(unsafe.Pointer(&logicalProcessors[0]), unsafe.Pointer(data.LogicalProcessors), C.size_t(data.NumThreads)*C.sizeof_int)

	// construct the core struct
	core.ID = int(data.ID)
	core.NumThreads = uint32(data.NumThreads)

	core.LogicalProcessors = make([]int, data.NumThreads)

	for i, val := range logicalProcessors {
		core.LogicalProcessors[i] = int(val)
	}

}

func (proc *Processor) String() string {

	return fmt.Sprintf("Processor ID: %d\nModel: %d\nPhysical cores: %d\nHardware threads: %d\nVendor: %s\nFeatures: %s", proc.ID, proc.Model, proc.NumCores, proc.NumThreads, proc.Vendor, proc.Capabilites)
}

func (core *ProcessorCore) String() string {
	var pus string = " "

	for _, pu := range core.LogicalProcessors {
		pus += strconv.Itoa(pu)
		pus += " "

	}
	return fmt.Sprintf("Core ID: %d\nCore Num threads: %d \nPUs: [%s]\n", core.ID, core.NumThreads, pus)
}

package cpu

// #cgo LDFLAGS: -L. -lprocessor
// #include <stdlib.h>
// #include "cpu-info/processor.h"
import "C"
import (
	"fmt"
	"strconv"
	"strings"
	"unsafe"

	"github.com/fatih/color"
)

func (proc *Processor) Get_proc_info() {
	p := C.get_proc_info()
	proc.ID = int(p.ID)
	proc.NumCores = uint32(p.NumCores)
	proc.NumThreads = uint32(p.NumThreads)
	proc.Model = int(p.Model)
	proc.Vendor = C.GoString(p.Vendor)
	proc.Capabilites = C.GoString(p.Capabilites)

	for i := 0; i < int(p.NumCores); i++ {
		core := new(ProcessorCore)
		core.Get_core_info(i, int(proc.NumThreads)/int(proc.NumCores))
		proc.Cores = append(proc.Cores, core)
	}

}

func (core *ProcessorCore) Get_core_info(i int, threads int) {

	c := C.ProcessorCore{}
	size := C.size_t(unsafe.Sizeof(c)) // get size to know how much to allocate for it in next step

	core_struct := C.malloc(size)
	defer C.free(core_struct)                                                  // harcoded for the moment
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

// stringify methods for CPU and Core types
func (proc *Processor) String() string {
	cores := make([]string, proc.NumCores)
	for _, val := range proc.Cores {
		cores = append(cores, val.String())
	}
	cores_str := strings.Join(cores, "")
	return fmt.Sprintf("Processor ID: %d\nModel: %d\nPhysical cores: %d\nHardware threads: %d\nVendor: %s\nFeatures: %s\n\n%s\n", proc.ID, proc.Model, proc.NumCores, proc.NumThreads, proc.Vendor, proc.Capabilites, cores_str)
}

func (core *ProcessorCore) String() string {
	var pus string = ""
	for _, pu := range core.LogicalProcessors {
		pus += strconv.Itoa(pu)
		pus += " "

	}
	red := color.New(color.FgRed).SprintFunc()
	return fmt.Sprintf("Core#%d\nPUs# [ %s ]\n", core.ID, red(pus))
}

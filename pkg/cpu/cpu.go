package cpu

// working on implementing Mac OS version for: github.com/jaypipes/ghw/pkg/cpu/cpu.go
type ProcessorCore struct {
	// ID is the `uint32` identifier that the host gave this core. Note that
	// this does *not* necessarily equate to a zero-based index of the core
	// within a physical package. For example, the core IDs for an Intel Core
	// i7 are 0, 1, 2, 8, 9, and 10
	ID int `json:"id"`
	// NumThreads is the number of hardware threads associated with the core
	NumThreads uint32 `json:"total_threads"` // NUMTHREADS/NUMCORES
	// LogicalProcessors is a slice of ints representing the logical processor
	// IDs assigned to any processing unit for the core. These are sometimes
	// called the "thread siblings". Logical processor IDs are the *zero-based*
	// index of the processor on the host and are *not* related to the core ID.
	LogicalProcessors []int `json:"logical_processors"` // Processing Unit, or (Logical) Processor
}
type Processor struct {
	// ID is the physical processor `uint32` ID according to the system
	ID int `json:"id"` // hw.packages
	// NumCores is the number of physical cores in the processor package
	NumCores uint32 `json:"total_cores"` // machdep.cpu.cores_per_package
	// NumThreads is the number of hardware threads in the processor package
	NumThreads uint32 `json:"total_threads"` // machdep.cpu.logical_per_package
	// Vendor is a string containing the vendor name
	Vendor string `json:"vendor"` // machdep.cpu.vendor
	// Model` is a string containing the vendor's model name
	Model int `json:"model"` // machdep.cpu.model
	// Capabilities is a slice of strings indicating the features the processor
	// has enabled
	Capabilites string           `json:"capabilities"` // machdep.cpu.features
	Cores       []*ProcessorCore `json:"cores"`
}

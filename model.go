package main

type Processor struct {
	// ID is the physical processor `uint32` ID according to the system
	ID int `json:"id"`
	// NumCores is the number of physical cores in the processor package
	NumCores uint32 `json:"total_cores"`
	// NumThreads is the number of hardware threads in the processor package
	NumThreads uint32 `json:"total_threads"`
	// Vendor is a string containing the vendor name
	Vendor string `json:"vendor"`
	// Model` is a string containing the vendor's model name
	Model string `json:"model"`
	// Capabilities is a slice of strings indicating the features the processor
	// has enabled
	Capabilities string `json:"capabilities"`
}

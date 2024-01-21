#include <sys/types.h>
#include <hwloc.h>


#ifndef PROCESSOR_H
#define PROCESSOR_H

typedef struct  {
    int ID;  // (ebx >> 24) & 0xFF
    u_int32_t NumCores; // machdep.cpu.core_count
    u_int32_t NumThreads; // machdep.cpu.cores_per_package
    int Model; // machdep.cpu.model
    char* Vendor; // machdep.cpu.vendor
    char* Capabilites; // machdep.cpu.features
    
} Processor;

typedef struct {
    int ID; // (ebx >> 26) & 0x3F
    u_int32_t NumThreads; //machdep.cpu.thread_count
    int LogicalProcessors[]; // Processing Unit(PU), or (Logical) Processor in hwloc this is cpuset;
    // hwloc  os_index obj field ??

} ProcessorCore;

#define INFO_LEN 5

#define NUMCORES "machdep.cpu.cores_per_package"
#define NUMTHREADS "machdep.cpu.logical_per_package"
#define MODEL "machdep.cpu.model"
#define CAPS "machdep.cpu.features"
#define CORE_NUM_THREADS "machdep.cpu.thread_count"
#define VENDOR "machdep.cpu.vendor"


void cpuid(unsigned int*,unsigned int*,unsigned int*,unsigned int*);
int get_proc_id();
Processor get_proc_info();
void report_err(const char* info);
void test();
int get_core_id();
ProcessorCore get_core_info();
void test_hwloc();
void iterate_topo(hwloc_topology_t topology, hwloc_obj_t obj,
                           int depth);


extern const char* cpu_info[];

enum cpu_info_fields {_NUMCORES,_NUMTHREADS,_VENDOR,_MODEL,_CAPS};

#endif
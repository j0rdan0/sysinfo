#include <sys/types.h>
#include <hwloc.h>  

#ifndef PROCESSOR_H
#define PROCESSOR_H

typedef struct  {
    int ID;  // (ebx >> 24) & 0xFF
    u_int32_t NumCores; // machdep.cpu.core_count ( correct)
    u_int32_t NumThreads; // machdep.cpu.logical_per_package ( correct)
    int Model; // machdep.cpu.model ( correct)
    char* Vendor; // machdep.cpu.vendor ( correct)
    char* Capabilites; // machdep.cpu.features ( correct)
    
} Processor;

typedef struct {
    int ID; // hwloc HWLOC_OBJ_CORE os_inde
    u_int32_t NumThreads; // NUMTHREADS/NUMCORES ( correct)
    int LogicalProcessors[]; // Processing Unit(PU), or (Logical) Processor in hwloc this is cpuset; 
    // hwloc HWLOC_OBJ_PU  os_index obj field;  those are the actual threads
} ProcessorCore;

#define INFO_LEN 5

#define NUMCORES "machdep.cpu.cores_per_package"
#define NUMTHREADS "machdep.cpu.logical_per_package"
#define MODEL "machdep.cpu.model"
#define CAPS "machdep.cpu.features"
#define CORE_NUM_THREADS "machdep.cpu.features" // NUMTHREADS/NUMCORES // this needs refactor
#define VENDOR "machdep.cpu.vendor"


void cpuid(unsigned int*,unsigned int*,unsigned int*,unsigned int*);
int get_proc_id();
Processor get_proc_info();
void report_err(const char* info);
void test();
int get_core_id();
ProcessorCore get_core_info(Processor proc,int id,hwloc_topology_t topo);
void test_hwloc();



extern const char* cpu_info[];

enum cpu_info_fields {_NUMCORES,_NUMTHREADS,_VENDOR,_MODEL,_CAPS};

#endif
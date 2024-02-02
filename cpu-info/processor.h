#include <sys/types.h>
#include <hwloc.h>  

#ifndef PROCESSOR_H
#define PROCESSOR_H

hwloc_topology_t topology; // global hwloc topology

// struct representing a Processor Core
typedef struct {
    int ID; // hwloc HWLOC_OBJ_CORE os_index field
    u_int32_t NumThreads; // NUMTHREADS/NUMCORES
    int* LogicalProcessors; // Processing Unit(PU), or (Logical) Processor
    // hwloc HWLOC_OBJ_PU os_index ield; those are the actual threads
} ProcessorCore;


// struct representing a Processor Package
typedef struct  {
    int ID;  // (ebx >> 24) & 0xFF // incorrect
    u_int32_t NumCores; // machdep.cpu.core_count 
    u_int32_t NumThreads; // machdep.cpu.logical_per_package
    int Model; // machdep.cpu.model
    char* Vendor; // machdep.cpu.vendor
    char* Capabilites; // machdep.cpu.features
    ProcessorCore Cores[8];
} Processor;

#define INFO_LEN 5

#define NUMCORES "machdep.cpu.cores_per_package"
#define NUMTHREADS "machdep.cpu.logical_per_package"
#define MODEL "machdep.cpu.model"
#define CAPS "machdep.cpu.features"
#define VENDOR "machdep.cpu.vendor"

void cpuid(unsigned int*,unsigned int*,unsigned int*,unsigned int*);
int get_proc_id();
Processor get_proc_info();
void report_err(const char* info);
void get_core_info(ProcessorCore* core,int id,int threads);
void test_hwloc();
void init_topology();
static inline void destroy_topology() {hwloc_topology_destroy(topology);}

extern const char* cpu_info[];

enum cpu_info_fields {_NUMCORES,_NUMTHREADS,_VENDOR,_MODEL,_CAPS};

#endif
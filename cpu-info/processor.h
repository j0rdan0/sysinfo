#include <sys/types.h>

#ifndef PROCESSOR_H
#define PROCESSOR_H

typedef struct  {
    int ID; 
    u_int32_t NumCores; // machdep.cpu.core_count
    u_int32_t NumThreads; // machdep.cpu.thread_count
    int Model; // machdep.cpu.model
    char* Vendor; // machdep.cpu.vendor
    char* Capabilites; // machdep.cpu.features
    
} Processor;

#define INFO_LEN 5

#define NUMCORES "machdep.cpu.core_count"
#define NUMTHREADS "machdep.cpu.thread_count"
#define VENDOR "machdep.cpu.vendor"
#define MODEL "machdep.cpu.model"
#define CAPS "machdep.cpu.features"


void cpuid(unsigned int*,unsigned int*,unsigned int*,unsigned int*);
int get_cpu();
Processor get_proc_info();
int report_err(const char* info);
void test();


extern const char* cpu_info[];

enum cpu_info_fields {_NUMCORES,_NUMTHREADS,_VENDOR,_MODEL,_CAPS};

#endif
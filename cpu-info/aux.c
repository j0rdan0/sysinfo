#include <stdio.h>
#include <stdlib.h>
#include "processor.h"
#include <hwloc.h>
#include <string.h>

const char* cpu_info[] = {NUMCORES,NUMTHREADS,VENDOR,MODEL,CAPS};

void cpuid(unsigned int *eax, unsigned int *ebx, unsigned int *ecx, unsigned int *edx) {
    asm volatile (
        "cpuid;"
        : "=a" (*eax), "=b" (*ebx), "=c" (*ecx), "=d" (*edx)
        : "a" (*eax), "c" (*ecx)
    );
}

int get_proc_id() {
	unsigned int eax,ebx,ecx,edx;
	eax = 1;
	ebx = ecx = edx = 0;
	cpuid(&eax,&ebx,&ecx,&edx);
	int proc_id = (ebx >> 24) & 0xFF; //  see https://www.felixcloutier.com/x86/cpuid
	return proc_id;
}
int get_core_id() {
	unsigned int eax,ebx,ecx,edx;
	eax = 1;
	ebx = ecx = edx = 0;
	cpuid(&eax,&ebx,&ecx,&edx);
	int core_id = (ebx >> 26) & 0x3F;
	return core_id;

}

// error handling requires more work
void report_err(const char* info) {
	char* err;
	sprintf(err,"%s err: ",info);
	perror(err);
	exit(EXIT_FAILURE);
}


void test() {
	Processor p = get_proc_info();
	printf("ID: %d cores: %d threads: %d vendor: %s model: %d caps: %s\n",p.ID,p.NumCores,p.NumThreads,p.Vendor,p.Model,p.Capabilites);
}

void test_hwloc() {
	hwloc_topology_t topo;
	hwloc_cpuset_t set;
	hwloc_obj_t obj;
	char type[32];
	
	int ret = hwloc_topology_init(&topo);
	if ( ret == -1) {
		perror("err: ");
		exit(EXIT_FAILURE);
	}
	printf("topo initiated at: %p\n",&topo);
	ret = hwloc_topology_load(topo);
	if ( ret == -1) {
		perror("err: ");
		hwloc_topology_destroy(topo);
		exit(EXIT_FAILURE);
		
	} 
	printf("loaded topology\n");
			
	Processor proc = get_proc_info();
	ProcessorCore p ;
	ProcessorCore logical[proc.NumCores];
	

	// create array of Cores
	for ( int i = 0 ; i < proc.NumCores ;i++) {
		logical[i] =  get_core_info(proc,i,topo);
	}
	

	hwloc_topology_destroy(topo);
}



	


	



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


void test_hwloc() {
	
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

	Processor p = get_proc_info();
	
	
	for ( int i = 0; i < p.NumCores;i++) {
		printf("Core#%d\n",p.Cores[i].ID);
		for ( int j = 0; j < p.Cores[i].NumThreads;j++) {
			printf("PU#%d\n",p.Cores[i].LogicalProcessors[j]);
		}
	}
	
	hwloc_topology_destroy(topo);
}



	


	



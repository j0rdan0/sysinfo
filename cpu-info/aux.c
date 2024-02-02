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

// this needs to be rewritten, processor id should be 0 or 1, since you mainly have only 1 CPU on Macs
int get_proc_id() {
	unsigned int eax,ebx,ecx,edx;
	eax = 1;
	ebx = ecx = edx = 0;
	cpuid(&eax,&ebx,&ecx,&edx);
	int proc_id = (ebx >> 24) & 0xFF; //  see https://www.felixcloutier.com/x86/cpuid
	return proc_id;
}

void report_err(const char* info) {
	char* err;
	sprintf(err,"%s err: ",info);
	perror(err);
	exit(EXIT_FAILURE);
}

void init_topology() {
	int ret = hwloc_topology_init(&topology);
	if ( ret == -1) {
		perror("err: ");
		exit(EXIT_FAILURE);
	}
	ret = hwloc_topology_load(topology);
	if ( ret == -1) {
		perror("err: ");
		hwloc_topology_destroy(topology);
		exit(EXIT_FAILURE);
		
	} 
	
}




	


	



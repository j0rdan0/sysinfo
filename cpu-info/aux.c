#include <stdio.h>
#include "processor.h"

const char* cpu_info[] = {NUMCORES,NUMTHREADS,VENDOR,MODEL,CAPS};

void cpuid(unsigned int *eax, unsigned int *ebx, unsigned int *ecx, unsigned int *edx) {
    asm volatile (
        "cpuid;"
        : "=a" (*eax), "=b" (*ebx), "=c" (*ecx), "=d" (*edx)
        : "a" (*eax), "c" (*ecx)
    );
}

int get_cpu() {
	unsigned int eax,ebx,ecx,edx;
	eax = 1;
	ebx = ecx = edx = 0;
	cpuid(&eax,&ebx,&ecx,&edx);
	int cpu_id = (ebx >> 24) & 0xFF; //  see https://www.felixcloutier.com/x86/cpuid
	return cpu_id;
}

// error handling requires more work
int report_err(const char* info) {
	char* err;
	sprintf(err,"%s err: ",info);
	return -1;
}


void test() {
	Processor p = get_proc_info();
	printf("ID: %d cores: %d threads: %d vendor: %s model: %d caps: %s\n",p.ID,p.NumCores,p.NumThreads,p.Vendor,p.Model,p.Capabilites);
}
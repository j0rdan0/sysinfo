#include <stdio.h>
#include <stdlib.h>
#include "processor.h"
#include <hwloc.h>
#include <strings.h>

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
	
	
	iterate_topo(topo,hwloc_get_root_obj(topo),0);
	

	hwloc_topology_destroy(topo);
}

void iterate_topo(hwloc_topology_t topology, hwloc_obj_t obj,
                           int depth) {

char type[32];
unsigned i;

 hwloc_obj_type_snprintf(type, sizeof(type), obj, 0);
 if( strcmp(type,"Core") == 0 || strcmp(type,"PU") == 0)
	{
		printf("type: %s",type);
 		if (obj->os_index != (unsigned) -1)
			printf("#%u\n",obj->os_index);
		else {
			printf("\n");
		}
	}					   
 	

for(i =0; i< obj->arity;i++) {
	iterate_topo(topology,obj->children[i],depth+1);
}
}


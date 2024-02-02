#include <stdio.h>
#include <stdlib.h>
#include "processor.h"
#include <hwloc.h>
#include <string.h>

const char* cpu_info[] = {NUMCORES,NUMTHREADS,VENDOR,MODEL,CAPS};

int get_proc_id() {
    init_topology();
	 hwloc_obj_t proc;
	 proc = hwloc_get_obj_by_type(topology, HWLOC_OBJ_PACKAGE, 0);
	 return proc->os_index;
	 destroy_topology();	
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




	


	



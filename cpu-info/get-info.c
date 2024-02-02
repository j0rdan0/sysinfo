#include <stdio.h>
#include <sys/sysctl.h>
#include <sys/types.h>
#include <stdlib.h>
#include "processor.h"

// main function to be exported to Go
 Processor get_proc_info() {
	
	Processor p;
	size_t data_size;
	int ret;
	
	// get CPU packet info
	for ( enum cpu_info_fields i = _NUMCORES; i <= _CAPS;i++) {
		switch(i) {
			case  _NUMCORES:
				data_size = sizeof(p.NumCores);
				ret = sysctlbyname(NUMCORES,&p.NumCores,&data_size,NULL,0);
				if (ret != 0) report_err(cpu_info[i]);
				break;

			case _NUMTHREADS:
				data_size = sizeof(p.NumThreads);
				ret = sysctlbyname(NUMTHREADS,&p.NumThreads,&data_size,NULL,0);
				if (ret != 0) report_err(cpu_info[i]);
				break; 

			case _MODEL:
				data_size = sizeof(p.Model);
				ret = sysctlbyname(MODEL,&p.Model,&data_size,NULL,0);
				if (ret != 0) report_err(cpu_info[i]);
				break;

			case _VENDOR:
				ret = sysctlbyname(VENDOR,NULL,&data_size,NULL,0);
				if (ret != 0) report_err(cpu_info[i]);

				p.Vendor = (char*)malloc(data_size);
				if (p.Vendor == NULL) report_err("malloc failed for vendor info");

				ret = sysctlbyname(VENDOR,p.Vendor,&data_size,NULL,0);
				if (ret != 0) report_err(cpu_info[i]);
				break;

			case _CAPS:
				ret = sysctlbyname(CAPS,NULL,&data_size,NULL,0);
				if (ret != 0) report_err(cpu_info[i]);

				p.Capabilites = (char*)malloc(data_size);
				if (p.Capabilites == NULL) report_err("malloc failed for features info");

				ret = sysctlbyname(CAPS,p.Capabilites,&data_size,NULL,0);
				if (ret != 0) report_err(cpu_info[i]);
				break;

		}
	}
	p.ID = get_proc_id();

/*
// get info for all cores;
	for ( int i = 0 ; i < p.NumCores ;i++) {
		 get_core_info(&p.Cores[i],i,p.NumThreads/p.NumCores);
	}	

	
*/
	return p;
}

 void get_core_info(ProcessorCore* core,int id,int threads) {
	init_topology();
	
	core->NumThreads = threads;
	core->ID = id;
	hwloc_obj_t pu;
/*
	Topology looks like this: Core -> 2 L1d -> 1 PU/L1
*/
	hwloc_obj_t core_obj = hwloc_get_obj_by_type(topology,HWLOC_OBJ_CORE,id);
	core->LogicalProcessors = malloc(sizeof(int)*core->NumThreads);
	
	for (int j = 0; j < core_obj->arity;j++) { // 2 PUs
		pu = core_obj->children[j]->children[0];
		*(core->LogicalProcessors+j) = (int)pu->os_index;		
	}
		
		destroy_topology();
}


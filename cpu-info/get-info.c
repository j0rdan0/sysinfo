#include <stdio.h>
#include <sys/sysctl.h>
#include <sys/types.h>
#include <stdlib.h>
#include "processor.h"

// main function to be exported to Go
Processor get_proc_info() {
	size_t data_size;
	int ret;
	Processor p;

	for ( enum cpu_info_fields i=_NUMCORES; i <= _CAPS;i++) {
		switch(i) {
			case  _NUMCORES:
				ret = sysctlbyname(NUMCORES,&p.NumCores,&data_size,NULL,0);
				if (ret != 0) report_err(cpu_info[i]);
				break;

			case _NUMTHREADS:
				ret = sysctlbyname(NUMTHREADS,&p.NumThreads,&data_size,NULL,0);
				if (ret != 0) report_err(cpu_info[i]);
				break; 

			case _MODEL:
				ret = sysctlbyname(MODEL,&p.Model,&data_size,NULL,0);
				if (ret != 0) report_err(cpu_info[i]);
				break;

			case _VENDOR:
				ret = sysctlbyname(VENDOR,NULL,&data_size,NULL,0);
				if (ret != 0) report_err(cpu_info[i]);

				p.Vendor = (char*)malloc(data_size);
				if (p.Vendor == NULL) report_err("malloc for vendor");

				ret = sysctlbyname(VENDOR,p.Vendor,&data_size,NULL,0);
				if (ret != 0) report_err(cpu_info[i]);
				break;

			case _CAPS:
				ret = sysctlbyname(CAPS,NULL,&data_size,NULL,0);
				if (ret != 0) report_err(cpu_info[i]);

				p.Capabilites= (char*)malloc(data_size);
				if (p.Capabilites == NULL) report_err("malloc for features");

				ret = sysctlbyname(CAPS,p.Capabilites,&data_size,NULL,0);
				if (ret != 0) report_err(cpu_info[i]);
				break;

		}
	}
	p.ID = get_proc_id();
		
	return p;
}

ProcessorCore get_core_info(Processor proc,int id,hwloc_topology_t topo) {
	ProcessorCore p;
	
	p.NumThreads = proc.NumThreads/proc.NumCores;
	hwloc_obj_t pu;

/*
	Topology looks like this:
	Core -> 2 L1d -> 1 PU/L1
*/

	hwloc_obj_t core = hwloc_get_obj_by_type(topo,HWLOC_OBJ_CORE,id);
	p.ID = id;
			
		for (int j = 0; j < core->arity;j++) { // 2 PUs
			//l1 = 
			pu = core->children[j]->children[0];
			p.LogicalProcessors[j] = (int)pu->os_index;
			
		}
	
	
	
	
	
	
	return p;

}


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
	p.ID = get_cpu();
		
	return p;
}


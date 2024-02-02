# sysinfo
Golang sysinfo implementation

---

 Working on creating Mac OS X implementation Go Module: github.com/jaypipes/ghw/

 Will eventually create a fork for it, currently working separately

 Decided to use hwloc lib for this (https://www.open-mpi.org/projects/hwloc/doc/v2.10.0/index.php#cli_examples) since some info is not that easy to be queries on Mac OS. Might just learn how things are implemented in hwloc for Mac and refactor.

 Have a working version now, but need to look further into how hwloc gets PU info and CPU ID, so I can implement this directly into my code, without having to depend on this lib

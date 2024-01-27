# sysinfo
Golang sysinfo implementation

---

 Working on creating Mac OS X implementation Go Module: github.com/jaypipes/ghw/

 Will eventually create a fork for it, currently working separately

 Decided to use hwloc lib for this (https://www.open-mpi.org/projects/hwloc/doc/v2.10.0/index.php#cli_examples) since some info is not that easy to be queries on Mac OS. Might just learn how things are implemented in hwloc for Mac and refactor.


 For passing struct info back to Go will need to use a struct pointer passed to C functions, as in struct-example.go; have problems in accessing dynamic array members from C struct, so will need to use pointer arithmetic for it;

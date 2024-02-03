source_files = pkg/cpu/cpu-info/aux.c pkg/cpu/cpu-info/get-info.c
lib_target = libprocessor.so
libs = -lhwloc

all:
	gcc -shared -o $(lib_target) $(source_files) $(libs)
	cp $(lib_target) ../.
clean:
	rm $(lib_target) 
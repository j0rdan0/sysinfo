lib = libprocessor.so
target_dir = cmd
target = sysinfo
lib_makefile = pkg/cpu/cpu-info/Makefile

all:
	make -f $(lib_makefile) # build libprocessor first
	go build -o $(target_dir)/$(target) . 
	cp $(lib) $(target_dir)
clean:
	rm $(target_dir)/$(lib) $(target_dir)/$(target)
	rm $(lib)
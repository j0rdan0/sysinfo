lib = libprocessor.so
target_dir = cmd
target = sysinfo
all:
	make -f cpu-info/Makefile # build libprocessor first
	go build -o $(target_dir)/$(target) . 
	cp $(lib) $(target_dir)
clean:
	rm $(target_dir)/$(lib) $(target_dir)/$(target)
	rm $(lib)
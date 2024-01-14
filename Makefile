lib = libprocessor.so
target_dir = cmd
target = sysinfo
all:
	go build -o $(target_dir)/$(target) .
	cp $(lib) $(target_dir)
clean:
	rm $(target_dir)/$(lib) $(target_dir)/$(target)
source_files = aux.c get-info.c
lib_target = libprocessor.so

all:
	gcc -shared -o $(lib_target) $(source_files)
	cp $(lib_target) ../.
clean:
	rm $(lib_target) 
all: mmap-read mmap-write mmap-fork

cc=gcc -g3

mmap-read: mmap-read.c
	$(cc) $^ -o $@

mmap-write: mmap-write.c
	$(cc) $^ -o $@

mmap-fork: mmap-fork.c
	$(cc) $^ -o $@

clean:
	rm mmap-read
	rm mmap-write
	rm mmap-fork

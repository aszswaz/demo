all: mmap-read mmap-write mmap-fork

cc=gcc -g3

mmap-read: mmap-read.c
	$(cc) mmap-read.c -o mmap-read

mmap-write: mmap-write.c
	$(cc) mmap-write.c -o mmap-write

mmap-fork: mmap-fork.c
	$(cc) mmap-fork.c -o mmap-fork

clean:
	rm mmap-read
	rm mmap-write

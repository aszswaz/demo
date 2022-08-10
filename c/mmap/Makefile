all: mmap-read mmap-write

cc=gcc -g3

mmap-read: mmap-read.c
	$(cc) mmap-read.c -o mmap-read

mmap-write: mmap-write.c
	$(cc) mmap-write.c -o mmap-write

clean:
	rm mmap-read
	rm mmap-write

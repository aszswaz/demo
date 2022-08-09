all: check-size sparse-files-01 sparse-files-02 sparse-files-03

sparse-files-01: sparse-files-01.c sparse-files.raw
	gcc sparse-files-01.c -o sparse-files-01

sparse-files-02: sparse-files-02.c sparse-files.raw
	gcc sparse-files-02.c -o sparse-files-02

sparse-files-03: sparse-files-03.c
	gcc sparse-files-03.c -o sparse-files-03

check-size: check-size.c
	gcc check-size.c -o check-size -lm

sparse-files.raw:
	dd if=/dev/zero of=sparse-files.raw bs=1 count=0 seek=50M

clean:
	rm sparse-files-01
	rm sparse-files-02
	rm sparse-files.raw
	rm check-size
	rm sparse-files-03

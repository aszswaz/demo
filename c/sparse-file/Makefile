all: check-size sparse-files-01 sparse-files-02 sparse-files-03 sparse-files.raw

cc=gcc -g3

sparse-files-01: sparse-files-01.c
	$(cc) $^ -o $@

sparse-files-02: sparse-files-02.c
	$(cc) $^ -o $@

sparse-files-03: sparse-files-03.c
	$(cc) $^ -o $@

check-size: check-size.c
	$(cc) $^ -o $@ -lm

sparse-files.raw:
	dd if=/dev/zero of=$@ bs=1 count=0 seek=50M

clean:
	rm sparse-files-01
	rm sparse-files-02
	rm sparse-files.raw
	rm check-size
	rm sparse-files-03

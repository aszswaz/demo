CFLAGS=-O0 -g3 -ggdb -Werror -Wextra
LIBRARY=-llua
CC=@gcc $(CFLAGS) $(LIBRARY)

all: capi01.so capi02

capi01.so: capi01.c
	$(CC) -fPIC -shared $< -o $@

capi02: capi02.c
	$(CC) $< -o $@

.PHONY: clean
clean:
	@rm -rf *.so
	@rm capi02

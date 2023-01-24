CFLAGS=-g3 -ggdb -Werror -Wextra -fPIC -shared -llua
CC=@gcc $(CFLAGS)

all: demo.so

demo.so: demo.c
	$(CC) $< -o $@

.PHONY: clean
clean:
	@rm -rf *.so

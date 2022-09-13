CFLAGS=-g3 -ggdb -Werror -Wextra
CC=@gcc $(CFLAGS)
BUILD_DIR=build

all: $(BUILD_DIR)/mmap-read \
	$(BUILD_DIR)/mmap-write \
	$(BUILD_DIR)/mmap-fork

$(BUILD_DIR)/mmap-read: mmap-read.c
	$(CC) $^ -o $@

$(BUILD_DIR)/mmap-write: mmap-write.c
	$(CC) $^ -o $@

$(BUILD_DIR)/mmap-fork: mmap-fork.c
	$(CC) $^ -o $@

.PHONY: clean
clean:
	@rm -rf $(BUILD_DIR)

BUILD_DIR=build
CFLAGS=-g3 -ggdb -Werror -Wextra
CC=gcc $(CFLAGS)

all: $(BUILD_DIR) $(BUILD_DIR)/thread_pool

$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/thread_pool.o: thread_pool.c
	$(CC) -c $< -o $@

$(BUILD_DIR)/thread_pool: test/main.c $(BUILD_DIR)/thread_pool.o
	$(CC) $^ -o $@

.PHONY: clean
clean:
	@rm -rf $(BUILD_DIR)

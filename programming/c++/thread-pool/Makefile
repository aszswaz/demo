BUILD_DIR=build
CFLAGS=-g3 -ggdb -Werror -Wextra
CC=g++ $(CFLAGS)

all: $(BUILD_DIR) $(BUILD_DIR)/demo

$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/demo: main.cpp $(BUILD_DIR)/ThreadPool.o
	$(CC) $^ -o $@

$(BUILD_DIR)/ThreadPool.o: ThreadPool.cpp ThreadPool.h Thread.h
	$(CC) -c $< -o $@

.PHONY: clean
clean:
	@rm -rf $(BUILD_DIR)

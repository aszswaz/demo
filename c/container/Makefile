BUILD_DIR=build
CFLAGS=-g3 -ggdb -Werror -Wextra
CC=@gcc $(CFLAGS)

all: $(BUILD_DIR) $(BUILD_DIR)/array_list

$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/array_list.o: array_list.c
	$(CC) -c $< -o $@

$(BUILD_DIR)/array_list: test/main.c $(BUILD_DIR)/array_list.o
	$(CC) $^ -o $@

.PHONY: clean
clean:
	@rm -rf $(BUILD_DIR)

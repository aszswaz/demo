BUILD_DIR=build
CFLAGS=-g3 -ggdb -Werror -Wextra -lssl -lcrypto
CC=@gcc $(CFLAGS)

all: $(BUILD_DIR) $(BUILD_DIR)/ssl

$(BUILD_DIR):
	@mkdir $(BUILD_DIR)

$(BUILD_DIR)/ssl: ssl.c
	$(CC) $< -o $@

.PHONY: clean
clean:
	@rm -rf $(BUILD_DIR)

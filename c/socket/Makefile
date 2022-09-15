BUILD_DIR=build
CFLAGS=-g3 -ggdb -Werror -Wextra
CC=@gcc $(CFLAGS)

all: $(BUILD_DIR) \
	$(BUILD_DIR)/tcp-server \
	$(BUILD_DIR)/tcp-client \
	$(BUILD_DIR)/udp-server \
	$(BUILD_DIR)/udp-client \
	$(BUILD_DIR)/unix-tcp-server \
	$(BUILD_DIR)/unix-tcp-client \
	$(BUILD_DIR)/unix-udp-server \
	$(BUILD_DIR)/unix-udp-client

$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/tcp-server: tcp-server.c
	$(CC) $< -o $@

$(BUILD_DIR)/tcp-client: tcp-client.c
	$(CC) $< -o $@

$(BUILD_DIR)/udp-server: udp-server.c
	$(CC) $< -o $@

$(BUILD_DIR)/udp-client: udp-client.c
	$(CC) $< -o $@

$(BUILD_DIR)/unix-tcp-server: unix-tcp-server.c
	$(CC) $< -o $@

$(BUILD_DIR)/unix-tcp-client: unix-tcp-client.c
	$(CC) $< -o $@

$(BUILD_DIR)/unix-udp-server: unix-udp-server.c
	$(CC) $< -o $@

$(BUILD_DIR)/unix-udp-client: unix-udp-client.c
	$(CC) $< -o $@

.PHONY: clean
clean:
	@rm -rf $(BUILD_DIR)

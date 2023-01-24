BUILD_DIR=build
CFLAGS=-g3 -ggdb -Werror -Wextra
cc=@gcc $(CFLAGS)

all: $(BUILD_DIR) check-size sparse-files-01 sparse-files-02 sparse-files-03 sparse-files.raw

$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/sparse-files-01: sparse-files-01.c
	$(cc) $^ -o $@

$(BUILD_DIR)/sparse-files-02: sparse-files-02.c
	$(cc) $^ -o $@

$(BUILD_DIR)/sparse-files-03: sparse-files-03.c
	$(cc) $^ -o $@

$(BUILD_DIR)/check-size: check-size.c
	$(cc) $^ -o $@ -lm

sparse-files.raw:
	@dd if=/dev/zero of=$@ bs=1 count=0 seek=50M

.PHONY: clean
clean:
	@rm -rf $(BUILD_DIR)
	@rm sparse-files.raw

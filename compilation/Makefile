BUILD_DIR=build
CFLAGS=-f elf
CC=@nasm $(CFLAGS)
LD=@ld -m elf_i386

all: $(BUILD_DIR) \
	$(BUILD_DIR)/main32 \
	$(BUILD_DIR)/demo

$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/main32: $(BUILD_DIR)/main32.o $(BUILD_DIR)/print32.o
	$(LD) $^ -o $@

$(BUILD_DIR)/main32.o: main32.asm
	$(CC) $< -o $@

$(BUILD_DIR)/print32.o: print32.asm
	$(CC) $< -o $@

$(BUILD_DIR)/demo: $(BUILD_DIR)/demo.o
	$(LD) $< -o $@

$(BUILD_DIR)/demo.o: demo.asm
	$(CC) $< -o $@

.PHONY: clean
clean:
	@rm -rf $(BUILD_DIR)

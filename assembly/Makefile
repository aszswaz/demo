BUILD_DIR=build
# CFLAGS=-f elf64
CFLAGS=-f elf
CC=@nasm $(CFLAGS)
LD=@ld -m elf_i386

all: $(BUILD_DIR) \
	$(BUILD_DIR)/main \
	$(BUILD_DIR)/demo \
	$(BUILD_DIR)/memory

$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/main: $(BUILD_DIR)/main.o $(BUILD_DIR)/print.o
	$(LD) $^ -o $@

$(BUILD_DIR)/main.o: main.asm
	$(CC) $< -o $@

$(BUILD_DIR)/print.o: print.asm
	$(CC) $< -o $@

$(BUILD_DIR)/demo: $(BUILD_DIR)/demo.o
	$(LD) $< -o $@

$(BUILD_DIR)/demo.o: demo.asm
	$(CC) $< -o $@

$(BUILD_DIR)/memory: $(BUILD_DIR)/memory.o
	$(LD) $< -o $@

$(BUILD_DIR)/memory.o: memory.asm
	$(CC) $< -o $@

.PHONY: clean
clean:
	@rm -rf $(BUILD_DIR)

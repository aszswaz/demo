BUILD_DIR=build
CC=@nasm -f elf
CC64=@nasm -f elf64
LD=@ld -m elf_i386
LD64=@ld

all: $(BUILD_DIR) \
	$(BUILD_DIR)/main \
	$(BUILD_DIR)/hello-world \
	$(BUILD_DIR)/hello-world02 \
	$(BUILD_DIR)/memory

$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/main: $(BUILD_DIR)/main.o $(BUILD_DIR)/print.o
	$(LD) $^ -o $@

$(BUILD_DIR)/main.o: main.asm
	$(CC) $< -o $@

$(BUILD_DIR)/print.o: print.asm
	$(CC) $< -o $@

$(BUILD_DIR)/hello-world: $(BUILD_DIR)/hello-world.o
	$(LD) $< -o $@

$(BUILD_DIR)/hello-world.o: hello-world.asm
	$(CC) $< -o $@

$(BUILD_DIR)/hello-world02.o: hello-world02.asm
	$(CC64) $< -o $@

$(BUILD_DIR)/hello-world02: $(BUILD_DIR)/hello-world02.o
	$(LD64) $< -o $@

$(BUILD_DIR)/memory: $(BUILD_DIR)/memory.o
	$(LD) $< -o $@

$(BUILD_DIR)/memory.o: memory.asm
	$(CC) $< -o $@

.PHONY: clean
clean:
	@rm -rf $(BUILD_DIR)

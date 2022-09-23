BUILD_DIR=build
CC=@nasm -f elf $< -o $@
CC64=@nasm -f elf64 $< -o $@
GCC=@gcc -m32
LD=@ld -m elf_i386
LD64=@ld

all: $(BUILD_DIR) \
	$(BUILD_DIR)/main \
	$(BUILD_DIR)/hello-world \
	$(BUILD_DIR)/hello-world02 \
	$(BUILD_DIR)/memory \
	$(BUILD_DIR)/c-demo \
	$(BUILD_DIR)/c-print

$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/main: $(BUILD_DIR)/main.o $(BUILD_DIR)/print.o
	$(LD) $^ -o $@

$(BUILD_DIR)/main.o: main.asm
	$(CC)

$(BUILD_DIR)/print.o: print.asm
	$(CC)

$(BUILD_DIR)/hello-world: $(BUILD_DIR)/hello-world.o
	$(LD) $< -o $@

$(BUILD_DIR)/hello-world.o: hello-world.asm
	$(CC)

$(BUILD_DIR)/hello-world02.o: hello-world02.asm
	$(CC64)

$(BUILD_DIR)/hello-world02: $(BUILD_DIR)/hello-world02.o
	$(LD64) $< -o $@

$(BUILD_DIR)/memory: $(BUILD_DIR)/memory.o
	$(LD) $< -o $@

$(BUILD_DIR)/memory.o: memory.asm
	$(CC)

$(BUILD_DIR)/add.o: add.asm
	$(CC)

$(BUILD_DIR)/c-demo.o: c-demo.c
	$(GCC) -c $< -o $@

$(BUILD_DIR)/c-demo: $(BUILD_DIR)/add.o $(BUILD_DIR)/c-demo.o
	$(GCC) $^ -o $@

$(BUILD_DIR)/c-print.o: c-print.asm
	$(CC)

$(BUILD_DIR)/c-print: $(BUILD_DIR)/c-print.o
	$(GCC) -no-pie $< -o $@

.PHONY: clean
clean:
	@rm -rf $(BUILD_DIR)

BUILD_DIR = build
CC=@gcc -o3 -g3 -ggdb -Werror -Wextra

pipeline=$(BUILD_DIR)/pipeline
popen=$(BUILD_DIR)/popen
pipecmd=$(BUILD_DIR)/pipecmd
exec=$(BUILD_DIR)/exec

utils.o=$(BUILD_DIR)/utils.o

all: $(BUILD_DIR) \
	$(pipeline) \
	$(popen) \
	$(pipecmd) \
	$(exec)

$(BUILD_DIR):
	@mkdir $(BUILD_DIR)

$(utils.o): utils.c
	$(CC) -c $< -o $@

$(pipeline): pipeline.c $(utils.o)
	$(CC) -c $< -o $@.o
	$(CC) $@.o $(utils.o) -lpipeline -o $@

$(pipecmd): pipecmd.c $(utils.o)
	$(CC) -c $< -o $@.o
	$(CC) $@.o $(utils.o) -lpipeline -o $@

$(popen): popen.c
	$(CC) $< -o $@

$(exec): exec.c $(utils.o)
	$(CC) -c $< -o $@.o
	$(CC) $@.o $(utils.o) -o $@

.PHONY: clean
clean:
	@rm -rf $(BUILD_DIR)

CC := emcc
CCFLAGS := -s ASSERTIONS=1 -s ALLOW_MEMORY_GROWTH=1 -s EXPORTED_RUNTIME_METHODS=["ccall","cwrap","getValue"] -s EXPORTED_FUNCTIONS="['_malloc', '_free']" -s EXPORT_ES6=1 -s MODULARIZE=1 -s TOTAL_MEMORY=1024MB

SRC_DIR := c_src
SRC_FILES := $(filter-out $(SRC_DIR)/main.c, $(wildcard $(SRC_DIR)/*.c))
OUTPUT_DIR := wasm
OUTPUT_FILE := build.js

$(OUTPUT_DIR)/$(OUTPUT_FILE): $(SRC_FILES)
	$(CC) $(CCFLAGS) $(SRC_FILES) -o $(OUTPUT_DIR)/$(OUTPUT_FILE)

cli: $(SRC_FILES)
	gcc -Wall -Wextra -g $(SRC_FILES) $(SRC_DIR)/main.c -o $(OUTPUT_DIR)/main

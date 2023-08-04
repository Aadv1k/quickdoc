@echo off

set OUTPUT_DIR=wasm

SET CC=emcc
SET CCFLAGS=-s ASSERTIONS=1 -s ALLOW_MEMORY_GROWTH=1 -s EXPORTED_RUNTIME_METHODS=["ccall","cwrap"] -s EXPORTED_FUNCTIONS="['_malloc', '_free']"  -s EXPORT_ES6=1 -s MODULARIZE=1

SET SRC_FILES=c_src/utils.c c_src/sobel.c c_src/crop.c

if not exist %OUTPUT_DIR% mkdir %OUTPUT_DIR%

%CC% %CCFLAGS% %SRC_FILES% -o %OUTPUT_DIR%/build.js

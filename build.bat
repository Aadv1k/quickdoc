@echo off

set OUTPUT_DIR=wasm

SET CC=emcc
SET CCFLAGS=-O2 -s ASSERTIONS=1 -s ALLOW_MEMORY_GROWTH=1 -s EXPORTED_RUNTIME_METHODS="ccall,cwrap" -s EXPORTED_FUNCTIONS="['_malloc', '_free']"  -s EXPORT_ES6=1 -s MODULARIZE=1 

SET SRC_FILES=c_src/utils.c

if not exist %OUTPUT_DIR% mkdir %OUTPUT_DIR%

%CC% %CCFLAGS% %SRC_FILES% -o %OUTPUT_DIR%/build.js

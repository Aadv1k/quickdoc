@echo off

set SOURCE_DIR=c_src
set OUTPUT_DIR=wasm

SET CC=emcc
SET CCFLAGS=-O2 -sASSERTIONS -sALLOW_MEMORY_GROWTH -s EXPORTED_RUNTIME_METHODS="ccall,cwrap" -s EXPORTED_FUNCTIONS="['_malloc', '_free']"  -s EXPORT_ES6=1 -s MODULARIZE=1 

if not exist %OUTPUT_DIR% mkdir %OUTPUT_DIR%

%CC% %CCFLAGS% %SOURCE_DIR%/sobel.c -o %OUTPUT_DIR%/sobel.js

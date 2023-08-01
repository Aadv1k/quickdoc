@echo off

set SOURCE_DIR=c_src
set OUTPUT_DIR=wasm

SET CCFLAGS=-s EXPORTED_RUNTIME_METHODS="ccall,cwrap" -s EXPORT_ES6=1 -s MODULARIZE=1 
SET CC=emcc

if not exist %OUTPUT_DIR% mkdir %OUTPUT_DIR%

%CC% %CCFLAGS% %SOURCE_DIR%/greet.c -o %OUTPUT_DIR%/greet.js

@echo off

set OUTPUT_DIR=wasm

if not exist %OUTPUT_DIR% mkdir %OUTPUT_DIR%

SET CC=emcc
SET CCFLAGS=-s ASSERTIONS=1 -s ALLOW_MEMORY_GROWTH=1 -s EXPORTED_RUNTIME_METHODS=["ccall","cwrap","getValue"] -s EXPORTED_FUNCTIONS="['_malloc', '_free']" -s EXPORT_ES6=1 -s MODULARIZE=1 -s TOTAL_MEMORY=1024MB


SET SRC_FILES=c_src/utils.c c_src/sobel.c c_src/crop.c c_src/threshold.c
SET OUTPUT_FILE=build.js

if "%1%" == "CLI" (
  SET CC=gcc
  SET CCFLAGS=-Wall -Wextra
  SET SRC_FILES=%SRC_FILES% c_src/main.c
  SET OUTPUT_FILE=main.exe
)

%CC% %CCFLAGS% %SRC_FILES% -o %OUTPUT_DIR%\%OUTPUT_FILE%

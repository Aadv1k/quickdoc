#!/bin/bash

SOURCE_DIR=c_src
OUTPUT_DIR=wasm

CCFLAGS="-s EXPORTED_RUNTIME_METHODS=ccall,cwrap -s EXPORT_ES6=1 -s MODULARIZE=1"
CC=emcc

mkdir -p "$OUTPUT_DIR"

$CC $CCFLAGS "$SOURCE_DIR/greet.c" -o "$OUTPUT_DIR/greet.js"

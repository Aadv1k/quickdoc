# Quickdoc

Quick utilities related to scanned documents

- Clean and properly crop the documents and convert them to pdf


## Setup

The project uses wasm for image processing, hence you will need [emscripten](https://emscripten.org), and `emcc` to build the necessary wasm files. 

Before running a live server you would need to build the files

### Windows

```
./build.bat
```

### Unix

```
./build.sh
```

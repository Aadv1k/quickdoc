# Quickdoc

> This tool is quite exploratory in nature, hence functionality may break or become unavaliable. Please feel free to raise an issue if this happens, thanks! 

Quickdoc is a [WebAssembly](https://webassembly.org/) based site that can **automatically** trim, de-noise and filter a image, similar to an [image scanner](https://en.wikipedia.org/wiki/Image_scanner)

## Features (to be)

- [ ] Auto crop, de-noise and filter the image to look like a scan
- [ ] some variation of an OCR system
- [ ] Convert scanned documents to PDF

## Setup

The project uses [emscripten](https://emscripten.org) to compile the C source to wasm

### Windows

```
./build.bat
```

### Unix

```
./build.sh
```

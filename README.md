# Quickdoc

> This tool is quite exploratory in nature, hence functionality may break or become unavaliable. Please feel free to raise an issue if this happens, thanks! 

Quickdoc is a [WebAssembly](https://webassembly.org/) based site that can **automatically** trim, de-noise and filter a image, similar to an [image scanner](https://en.wikipedia.org/wiki/Image_scanner)

## Features

- [X] Auto crop, de-noise and filter the image to look like a scan
- [ ] some variation of an OCR system
- [ ] Convert scanned documents to PDF

## Quickstart

all of the necessary files are provided within the 'wasm/' directory.

you can just clone the repo and run it in a server

## Bootstrap

The project uses [emscripten](https://emscripten.org) to compile the C source to wasm

```console
make
```

Additionally you can also build the processing applied to the image as a CLI

```console
make cli
.\wasm\main.exe
```

### Windows

To build without make, you can use batch files

```console
.\build.bat
```

And to build the CLI

```console
.\build.bat CLI
.\wasm\main.exe
```

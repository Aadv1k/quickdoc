# Quickdoc

Quick browser only utilities for scanned documents

- [ ] Auto clean, crop and convert the scanned document(s) to pdf
- [ ] OCR Support + Export document as word

## Setup

The project uses [WASM](https://webassembly.org/) for image processing, hence you will need [emscripten](https://emscripten.org), and `emcc` to compile the C source to wasm

> **Note**
> Unfortunately several browsers (including Chrome, Safari, and Internet Explorer) do not support ``file://`` XHR requests, and can’t load extra files needed by the HTML (like a ``.wasm`` file, or packaged file data as mentioned lower down). For these browsers you’ll need to serve the files using a local webserver
> *~ [taken from here](https://emscripten.org/docs/getting_started/Tutorial.html)*

### Windows

```
./build.bat
```

### Unix

```
./build.sh
```


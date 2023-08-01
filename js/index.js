import setupFileUploader from "/js/fileUploader.js";
import setupImageProcessor from "/js/imageProcessor.js";

if (typeof WebAssembly !== "object" && typeof WebAssembly.instantiate === "function") {
    throw new Error("[quickdoc] WASM is required")
}

setupFileUploader();
setupImageProcessor();

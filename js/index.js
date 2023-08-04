import setupFileUploader from "./fileUploader.js";
import setupImageProcessor from "./imageProcessor.js";

if (typeof WebAssembly !== "object" && typeof WebAssembly.instantiate === "function") {
    throw new Error("[quickdoc] WASM is required")
}

setupFileUploader();
setupImageProcessor();

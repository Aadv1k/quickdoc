import greetModule from "/wasm/greet.js";

function checkIfHasWasmOrPanic() {
    console.warn("[quickdoc] JS version of es6 or later is required for quickdoc to function");
    console.warn("[quickdoc] WASM is used to process images entirely in the frontend");
}

greetModule().then(instance => {
    (instance.cwrap("greet"))();
})

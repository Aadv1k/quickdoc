try {
    eval(") => {}")
} catch (SyntaxError) {
    document.getElementsByTagName("body")[0].innerHTML = "<h2>Unsupported browser, please see console for more info</h1>";
    console.warn("[quickdoc] JS version of es6 or later is required for quickdoc to function");
    console.warn("[quickdoc] WASM is used to process images entirely in the frontend");
}

console.info("JavaScript version OK");

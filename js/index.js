import greetModule from "/wasm/greet.js";


const MAX_FILES = 32; // TODO: this number is arbitiary


if (typeof WebAssembly !== "object" && typeof WebAssembly.instantiate === "function") {
    throw new Error("[quickdoc] WASM is required")
}

const fileInput = document.getElementById("fileInput");

function readFileAsBase64(file) {
    console.assert(typeof file === "object", "readFileAsBase64 consumes a File object");
    return new Promise((resolve, reject) => {
        let fileReader = new FileReader();
        fileReader.readAsDataURL(file);
        fileReader.onload = () => {
            resolve(fileReader.result);
        };

        fileReader.onerror = () => reject(fileReader.error);
    })
}

fileInput.addEventListener("change", async (e) => {
    if (e.target.files.length > MAX_FILES) {
        throw new Error("[quickdoc] max amount of files exceeded");
    }

    const image = new Image();
    image.src = await readFileAsBase64(e.target.files[0]);

    let canvas = document.getElementById("primaryCanvas");
    let context = canvas.getContext("2d");

    canvas.width = image.width;
    canvas.height = image.height;
    context.drawImage(image, 0, 0);
});

import greetModule from "/wasm/greet.js";
import sobelModule from "/wasm/sobel.js";


const MAX_FILES = 32; // TODO: this number is arbitiary

const selectedFiles = new Map();

const fileBox = document.getElementById("fileBox");
const fileInput = document.getElementById("fileInput");
const btnProceed = document.getElementById("btnProceed");
const imageContainer = document.getElementById("imageContainer");

btnProceed.classList.add("btn-disabled");

fileBox.addEventListener("click", () => fileInput.click())

fileBox.addEventListener("drop", async (e) => {
    e.preventDefault();
    const files = e.dataTransfer.files;
    if (files && files.length > 0) {
        for (const file of files) {

        if (selectedFiles.get(file.name)) continue;

        const image = new Image();
        image.src = await readFileAsBase64(file);

        selectedFiles.set(file.name, image.src);

        image.classList.add("img--thumb");
        document.getElementById("imageContainer").appendChild(image);
            
        }
    }
    fileBox.classList.remove('file-box--dragover');
})

fileBox.addEventListener("dragleave", (e) => {
    e.preventDefault();
    fileBox.classList.remove('file-box--dragover');
})

fileBox.addEventListener("dragover", (e) => {
    e.preventDefault();
    fileBox.classList.add('file-box--dragover');
})



if (typeof WebAssembly !== "object" && typeof WebAssembly.instantiate === "function") {
    throw new Error("[quickdoc] WASM is required")
}

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

function extractPixelDataFromBase64(data) {
    const image = new Image();
    image.src = data;

    const canvas = document.createElement("canvas");
    const context = canvas.getContext("2d");

    canvas.width = image.width;
    canvas.height = image.height;
    context.drawImage(image, 0, 0);


    return context.getImageData(0, 0, image.width, image.height);
}

const canvas = document.createElement("canvas");
const ctx = canvas.getContext("2d");

btnProceed.addEventListener("click", async () => {
  const Module = await sobelModule();

  for (const file of selectedFiles) {
    let cv_apply_sobel_filter = Module.cwrap("cv_apply_sobel_filter_rgba", "void", ["number", "number", "number", "number"]);

    const { width, height, data } = extractPixelDataFromBase64(file[1]); // ImageData object;
    const channels = 4;

    const ptr = Module._malloc(width * height * channels);
    let heap = new Uint8Array(Module.HEAPU8.buffer, ptr, width * height * channels);
    heap.set(data);

    cv_apply_sobel_filter(ptr, width, height, channels); 

    data.set(heap);

    // Display the processed image on the canvas without creating a new canvas element
    canvas.width = width;
    canvas.height = height;
    const imageData = new ImageData(new Uint8ClampedArray(data, data.byteOffset, data.length), width, height);
    ctx.putImageData(imageData, 0, 0);
    imageContainer.appendChild(canvas);

    Module._free(ptr);
    heap = null;
  }

  selectedFiles.clear();
});

fileInput.addEventListener("change", async (e) => {
    btnProceed.classList.remove("btn-disabled");

    let files = e.target.files;
    if (files.length > MAX_FILES) {
        throw new Error("[quickdoc] max amount of files exceeded");
    }

    for (const file of files) {
        if (selectedFiles.get(file.name)) continue;

        const image = new Image();
        image.src = await readFileAsBase64(file);

        selectedFiles.set(file.name, image.src);

        image.classList.add("img--thumb");
        imageContainer.appendChild(image);
    }
});

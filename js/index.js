import greetModule from "/wasm/greet.js";


const MAX_FILES = 32; // TODO: this number is arbitiary

const selectedFiles = new Map();

const fileBox = document.getElementById("fileBox");
const fileInput = document.getElementById("fileInput");
const btnProceed = document.getElementById("btnProceed");

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


btnProceed.addEventListener("click", () => {
    console.log(selectedFiles);
})

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
        document.getElementById("imageContainer").appendChild(image);
    }
});

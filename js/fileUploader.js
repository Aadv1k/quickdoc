import ImagePreviewComponent from "./ImagePreviewComponent.js";

const MAX_FILES = 32; // TODO: this number is arbitiary

let SelectedFiles = new Set();

const readFileAsBase64 = (file) => {
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

const handleFileBoxDrop = async (event) => {
    event.preventDefault();
    const files = event.dataTransfer.files;

    if (files && files.length > 0) {
        btnProceed.classList.remove("btn--disabled");
        for (const file of files) {
            if (!file.type.startsWith("image")) continue;
            if (SelectedFiles.has(file.name)) continue;

            const imagePreviewComponent = new ImagePreviewComponent(await readFileAsBase64(file), null, (e) => {
                e.target.parentElement.remove();
            }, (e) => {}, false);
            document.getElementById("imageContainer").appendChild(imagePreviewComponent);
        }
    }
    event.target.classList.remove('file-box--active');
}

const handleFileBoxDragover = (event) => {
    event.preventDefault();
    event.target.classList.add('file-box--active');
}

const handleFileBoxDragleave = (event) => {
    event.preventDefault();
    event.target.classList.remove('file-box--active');
}

const handleFileInputChange = async (event) => {
    btnProceed.classList.remove("btn--disabled");

    let files = event.target.files;
    if (files.length > MAX_FILES) {
        throw new Error("[quickdoc] max amount of files exceeded");
    }

    for (const file of files) {
        if (SelectedFiles.has(file.name)) continue;

        const imagePreviewComponent = new ImagePreviewComponent(await readFileAsBase64(file), null, (e) => {
            e.target.parentElement.remove();
        }, (e) => {}, false);
        document.getElementById("imageContainer").appendChild(imagePreviewComponent);
    }
}


export default function setupFileUploader() {
    const fileBox = document.getElementById("fileBox");
    const fileInput = document.getElementById("fileInput");

    fileBox.addEventListener("click", () => fileInput.click())
    fileBox.addEventListener("drop", handleFileBoxDrop)
    fileBox.addEventListener("dragover", handleFileBoxDragover)
    fileBox.addEventListener("dragleave", handleFileBoxDragleave)

    fileInput.addEventListener("change", handleFileInputChange)
}

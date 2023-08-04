import SelectedFileMap from "./SelectedFileMap.js"

const MAX_FILES = 32; // TODO: this number is arbitiary

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
            if (SelectedFileMap.get(file.name)) continue;

            const image = new Image();
            image.src = await readFileAsBase64(file);

            SelectedFileMap.set(file.name, image.src);
        }
    }
    event.target.classList.remove('file-box--active');
    renderImagePreviews();
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
        if (SelectedFileMap.has(file.name)) continue;

        const image = new Image();
        image.src = await readFileAsBase64(file);

        SelectedFileMap.set(file.name, image.src);
    }

    renderImagePreviews();
}


function renderImagePreviews() {
  imageContainer.innerHTML = "";

  for (const [imgName, imgData] of SelectedFileMap) {
    const imagePreviewComponent = document.createElement("div");
    imagePreviewComponent.classList.add("preview");
    imagePreviewComponent.setAttribute("data-value", imgName);

    const image = new Image();
    image.src = imgData;
    image.classList.add("thumbnail");
    imagePreviewComponent.appendChild(image);

    const p = document.createElement("p");
    p.innerText = imgName;
    imagePreviewComponent.appendChild(p);

    const button = document.createElement("button");
    button.classList.add("btn");
    button.classList.add("close");
    button.innerText = "X";
    button.addEventListener("click", (e) => {
        SelectedFileMap.delete(e.target.parentElement.getAttribute("data-value"));
        e.target.parentElement.remove();
    })
    imagePreviewComponent.appendChild(button);


    imageContainer.appendChild(imagePreviewComponent);
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

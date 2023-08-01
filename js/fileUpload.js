import SelectedFileMap from "/js/SelectedFileMap.js"


const MAX_FILES = 32; // TODO: this number is arbitiary

const fileBox = document.getElementById("fileBox");
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

fileBox.addEventListener("click", () => fileInput.click())
fileBox.addEventListener("drop", async (e) => {
    e.preventDefault();
    const files = e.dataTransfer.files;
    if (files && files.length > 0) {

        btnProceed.classList.remove("btn-disabled");
        for (const file of files) {

            if (SelectedFileMap.get(file.name)) continue;

            const image = new Image();
            image.src = await readFileAsBase64(file);

            SelectedFileMap.set(file.name, image.src);

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



fileInput.addEventListener("change", async (e) => {
    btnProceed.classList.remove("btn-disabled");

    let files = e.target.files;
    if (files.length > MAX_FILES) {
        throw new Error("[quickdoc] max amount of files exceeded");
    }

    for (const file of files) {
        if (SelectedFileMap.get(file.name)) continue;

        const image = new Image();
        image.src = await readFileAsBase64(file);

        SelectedFileMap.set(file.name, image.src);

        image.classList.add("img--thumb");
        imageContainer.appendChild(image);
    }
});

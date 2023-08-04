export default function createImagePreviewComponent(base64Image, imageName, onDelete, onDownload, isDownloadable) {
    const imagePreviewComponent = document.createElement("div");
    imagePreviewComponent.classList.add("preview");

    imagePreviewComponent.setAttribute("data-value", imageName);

    const image = new Image();
    image.src = base64Image;
    image.classList.add("thumbnail");
    imagePreviewComponent.appendChild(image);

    const button = document.createElement("button");
    button.classList.add("btn");
    button.innerText = "X";
    button.addEventListener("click", onDelete);
    imagePreviewComponent.appendChild(button);

    if (isDownloadable) {
        const downloadButton = document.createElement("button");
        downloadButton.classList.add("btn");
        downloadButton.classList.add("download");
        downloadButton.innerText = "DL";
        downloadButton.addEventListener("click", onDownload);
        imagePreviewComponent.appendChild(downloadButton);
    }

    return imagePreviewComponent;
}

export default function createImagePreviewComponent(base64Image, width, height, isDownloadable) {
    const imagePreviewComponent = document.createElement("div");
    imagePreviewComponent.classList.add("preview");

    const image = new Image();
    image.src = base64Image;
    image.width = width;
    image.height = height;
    image.classList.add("thumbnail");
    imagePreviewComponent.appendChild(image);

    const button = document.createElement("button");
    button.classList.add("btn");
    button.innerText = "X";
    button.addEventListener("click", (e) => {
        e.target.parentElement.remove();
    })
    imagePreviewComponent.appendChild(button);

    if (isDownloadable) {
        const downloadButton = document.createElement("button");
        downloadButton.classList.add("btn");
        downloadButton.classList.add("download");
        downloadButton.innerText = "DL";
        downloadButton.addEventListener("click", (e) => {
            const downloadLink = document.createElement('a');
            downloadLink.href = canvas.toDataURL();
            downloadLink.download = "image";
            downloadLink.click();
            downloadLink.remove();
        })
        imagePreviewComponent.appendChild(downloadButton);
    }

    return imagePreviewComponent;
}

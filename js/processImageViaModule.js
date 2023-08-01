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

export default function processImageViaModule(imgData, Module) {
    let cv_apply_sobel_filter = Module.cwrap("cv_apply_sobel_filter_rgba", "void", ["number", "number", "number", "number"]);

    const { width, height, data } = imgData;
    const channels = 4;

    const ptr = Module._malloc(width * height * channels);
    let heap = new Uint8Array(Module.HEAPU8.buffer, ptr, width * height * channels);
    heap.set(data);

    cv_apply_sobel_filter(ptr, width, height, channels); 

    data.set(heap);

    /* DO SOMETHING HERE */

    Module._free(ptr);
    heap = null;

}

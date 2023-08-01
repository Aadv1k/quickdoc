import SobelModule from "/wasm/sobel.js";
import ResizeModule from "/wasm/resize.js";
import SelectedFileMap from "/js/SelectedFileMap.js";

const extractPixelDataFromBase64 = (data) => {
    const image = new Image();
    image.src = data;

    const canvas = document.createElement("canvas");
    const context = canvas.getContext("2d");

    canvas.width = image.width;
    canvas.height = image.height;
    context.drawImage(image, 0, 0);

    return context.getImageData(0, 0, image.width, image.height);
}
  
const handleProceedClick = async (event) => {
    const sobelModule = await SobelModule();
    const resizeModule = await ResizeModule();

    for (const [imageName, base64Image] of SelectedFileMap) {

        const imgData = extractPixelDataFromBase64(base64Image);

        let cv_apply_sobel_filter = sobelModule.cwrap("cv_apply_sobel_filter_rgba", "void", ["number", "number", "number", "number"]);

        let { width, height, data } = imgData;
        const channels = 4;

        const ptr = sobelModule._malloc(width * height * channels);
        let heap = new Uint8Array(sobelModule.HEAPU8.buffer, ptr, width * height * channels);
        heap.set(data);

        cv_apply_sobel_filter(ptr, width, height, channels); 

        const sobelFilteredData = new Uint8ClampedArray(heap);

        /* THIS IS TEMP */
        const canvas = document.createElement("canvas");
        const context = canvas.getContext("2d");

        canvas.width = width;
        canvas.height = height;

        const id = new ImageData(sobelFilteredData, width, height);
        context.putImageData(id, 0, 0);

        document.body.appendChild(canvas);

        /****************/

        sobelModule._free(ptr);
        heap = null;
    }
    SelectedFileMap.clear();
}

export default function setupImageProcessor() {
    const btnProceed = document.getElementById("btnProceed");

    btnProceed.classList.add("btn-disabled");
    btnProceed.addEventListener("click", handleProceedClick);
}

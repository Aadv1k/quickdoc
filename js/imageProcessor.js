import InitModule from "/wasm/build.js";
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
  const Module = await InitModule();
  for (const [imageName, base64Image] of SelectedFileMap) {
    let { data, width, height } = extractPixelDataFromBase64(base64Image);
    let channels = 4;

    let imageBytes = new Uint8Array(data.buffer);
    let imageSize = width * height * channels;

    var buffer = Module._malloc(imageSize);
    Module.HEAPU8.set(imageBytes, buffer);

    var grayscaleBuffer = Module._malloc(width * height);
    Module.ccall("cv_squish_rgba_to_grayscale", "number", ["number", "number", "number", "number", "number"], [buffer, grayscaleBuffer, width, height, 4]);
    var sobelEdgeBuffer = Module._malloc(width * height);
    Module.HEAPU8.set(Module.HEAPU8.subarray(grayscaleBuffer, grayscaleBuffer + width * height), sobelEdgeBuffer);
    Module.ccall("cv_apply_sobel_filter_grayscale", null, ["number", "number", "number", "number", "number"], [grayscaleBuffer, sobelEdgeBuffer, width, height, 1])

    let leftEdge = Module.ccall("cv_get_left_edge", "number", ["number", "number", "number", "number"], [sobelEdgeBuffer, width, height, 1]);

    // TODO: this doesn't work as expected; it ends up either out of bounds or chopping of wayy to much
    // let rightEdge = Module.ccall("cv_get_right_edge", "number", ["number", "number", "number", "number"], [sobelEdgeBuffer, width, height, 1]);

    width = Module.ccall("cv_crop_x_edge_grayscale_and_get_width", null, ["number", "number", "number", "number", "number"], [grayscaleBuffer, width, height, 1, leftEdge, width]);
    imageSize = width * height * channels;

    Module.ccall("cv_expand_grayscale_to_rgba", null, ["number", "number", "number", "number"], [grayscaleBuffer, buffer, width, height, 1]);

    let modifiedBytes = Module.HEAPU8.subarray(buffer, buffer + imageSize);
    imageBytes.set(modifiedBytes);
    imageBytes = imageBytes.subarray(0, imageSize);

    Module._free(buffer);
    Module._free(grayscaleBuffer);
    Module._free(sobelEdgeBuffer);

    const canvas = document.createElement("canvas");
    const context = canvas.getContext("2d");

    const processedImageData = new ImageData(new Uint8ClampedArray(imageBytes), width, height);

    canvas.width = width;
    canvas.height = height;

    context.putImageData(processedImageData, 0, 0);

    document.body.appendChild(canvas);
  }
};


export default function setupImageProcessor() {
    const btnProceed = document.getElementById("btnProceed");

    btnProceed.classList.add("btn-disabled");
    btnProceed.addEventListener("click", handleProceedClick);
}

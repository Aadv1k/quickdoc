import OtsuModule from "/wasm/global.js";
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
  const otsuModule = await OtsuModule();

  for (const [imageName, base64Image] of SelectedFileMap) {
    const imgData = extractPixelDataFromBase64(base64Image);

    let cv_apply_otsu_threshold_rgba = otsuModule.cwrap(
      "cv_apply_otsu_threshold_rgba",
      "void",
      ["number", "number", "number", "number"]
    );

    let { width, height, data } = imgData;
    const channels = 4;

    const ptr = otsuModule._malloc(width * height * channels);
    let heap = new Uint8Array(otsuModule.HEAPU8.buffer, ptr, width * height * channels);
    heap.set(data);

    cv_apply_otsu_threshold_rgba(ptr, width, height, channels);

    // Create a copy of the processed data
    const processedData = new Uint8Array(heap);

    otsuModule._free(ptr);

    /* THIS IS TEMP */
    const canvas = document.createElement("canvas");
    const context = canvas.getContext("2d");

    canvas.width = width;
    canvas.height = height;

    const id = new ImageData(new Uint8ClampedArray(processedData), width, height);
    context.putImageData(id, 0, 0);

    document.body.appendChild(canvas);

    /****************/
  }
  SelectedFileMap.clear();
};


export default function setupImageProcessor() {
    const btnProceed = document.getElementById("btnProceed");

    btnProceed.classList.add("btn-disabled");
    btnProceed.addEventListener("click", handleProceedClick);
}

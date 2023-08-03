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
    const { data, width, height } = extractPixelDataFromBase64(base64Image);
    let channels = 4;

    let imageBytes = new Uint8Array(data.buffer);

    var buffer = Module._malloc(imageBytes.length * imageBytes.BYTES_PER_ELEMENT);
    Module.HEAPU8.set(imageBytes, buffer);

      /*
    const cv_apply_sobel_filter_rgba = Module.cwrap(
        "cv_apply_sobel_filter_rgba", null,
        ["number", "number", "number", "number"]
    cv_apply_sobel_filter_rgba(buffer, width, height, channels);
    */

    Module.ccall("cv_apply_sobel_filter_rgba", null, ["number", "number", "number", "number"], [buffer, width, height, channels]);
    Module._free(buffer);
  }
};


      /* RENDER IT 
    const canvas = document.createElement("canvas");
    const context = canvas.getContext("2d");

    canvas.width = width;
    canvas.height = height;

    context.putImageData(processedImageData, 0, 0);

    document.body.appendChild(canvas);
      
      /*******/

    // convert to grayscale for better computation
    // use sobel to determine the "paper"
    // -> on detecting a "white pixel group" set all the preceding pixels to black. reverse and do the same
    // rotate the image, EG shift all the valid pixels immediately to the start
    // clean up and resize baby
    // apply thresholding


export default function setupImageProcessor() {
    const btnProceed = document.getElementById("btnProceed");

    btnProceed.classList.add("btn-disabled");
    btnProceed.addEventListener("click", handleProceedClick);
}

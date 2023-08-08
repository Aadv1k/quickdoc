import InitModule from "../wasm/build.js";
import ImagePreviewComponent from "./ImagePreviewComponent.js";

const GRAYSCALE = 1,
      RGBA = 4;

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
  const imageContainer = document.getElementById("imageContainer").children;

  const Module = await InitModule();

  const copyBuffer = (dest, src, size) => {
    Module.HEAPU8.set(Module.HEAPU8.subarray(src, src + size), dest);
  }

  for (const previewComponent of imageContainer) {
    let base64Image = previewComponent?.getElementsByTagName("img")[0]?.src;

    let { data, width, height } = extractPixelDataFromBase64(base64Image);
    let channels = 4;

    let imageBytes = new Uint8Array(data.buffer);
    let imageSize = width * height * channels;

    var buffer = Module._malloc(imageSize);
    Module.HEAPU8.set(imageBytes, buffer);

    Module.ccall("cv_squish_rgba_to_grayscale", null, ["number", "number", "number", "number"], [buffer, width, height, channels]);
    channels = 1;

    var copiedBuffer = Module._malloc(imageSize);
    copyBuffer(copiedBuffer, buffer, imageSize);

    Module.ccall("cv_apply_sobel_filter_grayscale", null, ["number", "number", "number", "number"], [copiedBuffer, width, height, channels]);

    let leftEdge = Module.ccall("cv_get_left_edge", "number", ["number", "number", "number", "number", "number"], [copiedBuffer, width, height, channels, 0]);
      console.log(leftEdge);
    let rightEdge = Module.ccall("cv_get_left_edge", "number", ["number", "number", "number", "number", "number"], [copiedBuffer, width, height, channels, leftEdge + 10]);
    width = Module.ccall("cv_crop_x_edge_grayscale_and_get_width", "number", ["number", "number", "number", "number", "number", "number", "number"], [buffer, width, height, channels, leftEdge, rightEdge]);

    Module.ccall("cv_apply_threshold", null, ["number", "number", "number", "number"], [buffer, width, height, channels, 128]);
    Module.ccall("cv_expand_grayscale_to_rgba", null, ["number", "number", "number", "number"], [buffer, width, height, channels]);

    Module._free(buffer);
    Module._free(copiedBuffer);

    const canvas = document.createElement("canvas");
    const context = canvas.getContext("2d");

    imageSize = width * height * 4;

    const uint8ClampedArray = new Uint8ClampedArray(Module.HEAPU8.subarray(buffer, buffer + imageSize));
    const processedImageData = new ImageData(uint8ClampedArray, width, height);

    canvas.width = width;
    canvas.height = height;

    context.putImageData(processedImageData, 0, 0);

    const imagePreviewComponent = new ImagePreviewComponent(canvas.toDataURL(), null, (e) => {
      e.target.parentElement.remove();
    }, (e) => {
      const downloadLink = document.createElement('a');
      downloadLink.href = canvas.toDataURL();
      downloadLink.download = "image";
      downloadLink.click();
      downloadLink.remove();
    }, true);
    document.getElementById("outputContainer").appendChild(imagePreviewComponent);
  }
};

export default function setupImageProcessor() {
    const btnProceed = document.getElementById("btnProceed");

    btnProceed.classList.add("btn--disabled");
    btnProceed.addEventListener("click", handleProceedClick);
}

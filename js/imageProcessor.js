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
  console.log("I was invoked");

  for (const [imageName, base64Image] of SelectedFileMap) {
    const imgData = extractPixelDataFromBase64(base64Image);
    console.log(imgData);

    // convert to grayscale for better computation
    // use laplacian to determine the "paper"
    // -> on detecting a "white pixel group" set all the preceding pixels to black. reverse and do the same
    // rotate the image, EG shift all the valid pixels immediately to the start
    // clean up and resize baby
    // apply thresholding
  }
};


export default function setupImageProcessor() {
    const btnProceed = document.getElementById("btnProceed");

    btnProceed.classList.add("btn-disabled");
    btnProceed.addEventListener("click", handleProceedClick);
}

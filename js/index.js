import greetModule from "/wasm/greet.js";
import sobelModule from "/wasm/sobel.js";

import processImageViaModule from "/js/processImageViaModule.js";
import SelectedFileMap from "/js/SelectedFileMap.js";

import "/js/fileUpload.js";

const btnProceed = document.getElementById("btnProceed");
const imageContainer = document.getElementById("imageContainer");

if (typeof WebAssembly !== "object" && typeof WebAssembly.instantiate === "function") {
    throw new Error("[quickdoc] WASM is required")
}


btnProceed.classList.add("btn-disabled");
btnProceed.addEventListener("click", async () => {
  const module = await sobelModule();

  for (const base64Image of SelectedFileMap) {
      const imgData = extractPixelDataFromBase64(base64Image);
      processImageViaModule(imgData, module);
  }

  SelectedFileMap.clear();
});


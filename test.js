const addon = require("./build/Release/ccfits-native");
const { createCanvas, ImageData } = require("canvas");
const fs = require("fs");

function scurve(value, k, a) {

  return Math.pow((1 / (1+Math.exp(-k*value))), a);
}

const main = async () => {
  fits = new addon.Fits(process.argv[2]);

  await fits.open();
  hdu = await fits.pHDU();

  console.log(hdu.comment());
  console.log(hdu.axes());
  console.log(hdu.bitpix());
  console.log(hdu.keyWord());

  const keywords = hdu.keyWord();
  const axes = hdu.axes();
  const fitsimage8 = await hdu.read(); // return 8 bits Buffer
  const fitsimage16 = new Uint16Array(fitsimage8.buffer); // access buffer as 16 bit words

  const max = fitsimage16.reduce((c, p) => {
    return c > p ? c : p;
  }, 0);

  // draw in canvas
  const canvas = createCanvas(axes[0], axes[1]);
  const ctx = canvas.getContext("2d");
  const imgdata = new ImageData(axes[0], axes[1]);

  for (let i = 0; i < axes[1]; i++) {
    for (let j = 0; j < axes[0]; j++) {
      // apply a tanh curve
      const value = Math.tanh((fitsimage16[i * axes[0] + j] / max) * 3) * 255;
      //const value = scurve(fitsimage16[i * axes[0] + j]/max, 0.5, 1.0)*255;

      imgdata.data[4 * i * axes[0] + 4 * j] = value; // R
      imgdata.data[4 * i * axes[0] + 4 * j + 1] = value; // G
      imgdata.data[4 * i * axes[0] + 4 * j + 2] = value; // B
      imgdata.data[4 * i * axes[0] + 4 * j + 3] = 255; // A
    }
  }

  ctx.putImageData(imgdata, 0, 0);

  console.log("writing PNG...");
  await fs.promises.writeFile("test.png", canvas.toBuffer("image/png"));
  console.log("PNG writed");
};

main();

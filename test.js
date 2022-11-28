addon = require("./build/Release/ccfits-native");

fits = new addon.Fits();

hdu = fits.load();

console.log(hdu.comment());
console.log(hdu.axes());
console.log(hdu.bitpix());
console.log(hdu.keyWord());

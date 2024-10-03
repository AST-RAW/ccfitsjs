var addon = require("bindings")("ccfits-native");

interface keyWord {
  [index: string]: number | string;
}

interface pHDU {
  comment(): string;
  axes(): number[];
  bitpix(): number;
  keyWord(): keyWord;
  read(): Promise<Buffer>;
}

interface Fits {
  new (file: string): Fits;
  open(): Promise<boolean>;
  pHDU(): Promise<pHDU>;
}

export const Fits: Fits = addon.Fits;

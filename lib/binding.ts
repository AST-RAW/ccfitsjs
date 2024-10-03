var addon = require("bindings")("ccfits-native");

interface Keyword {
  [index: string]: number | string;
}

interface PHDU {
  getComment(): string;
  getAxes(): number[];
  getBitpix(): number;
  getKeyword(): Keyword;
  read(): Promise<Buffer>;
}

interface Fits {
  new (file: string): Fits;
  open(): Promise<boolean>;
  getPHDU(): Promise<PHDU>;
}

export const Fits: Fits = addon.Fits;

CCfitsjs
===

A nodejs wrapper of the ccfits library

The CCfits library provides an interface that allows the user to manipulate FITS format data through the high-level building blocks of FITS files and Header-Data Units (HDUs).

Installation
---

```
npm install @astraw/ccfitsjs
```

Usage
---

```
import { Fits } from "@astraw/ccfitsjs";

const open = async (filename: string) => {
  const fits = new Fits(filename);
  await fits.open();
  const phdu = await fits.getPHDU();

  console.log(phdu.getAxes());
  console.log(phdu.getComment());
  console.log(phdu.getKeyword());

  const buffer = await phdu.read();
};

open(process.argv[2]);
```

CCFitsjs
===

A nodejs wrapper of the ccfits library

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
  const phdu = await fits.pHDU();

  console.log(phdu.axes());
  console.log(phdu.comment());
  console.log(phdu.keyWord());

  const buffer = await phdu.read();
};

open(process.argv[2]);
```

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

```typescript
import { Fits } from "@astraw/ccfitsjs";

const open = async (filename: string) => {
  const fits = new Fits(filename);
  await fits.open();
  const phdu = await fits.getPHDU();

  console.log(phdu.getAxes());
  console.log(phdu.getComment());
  console.log(phdu.getKeyword());
  console.log(phdu.getBitpix());

  const data = await phdu.read();
  const data16b = new Uint16Array(data.buffer); // for a 16bit access
  const axes = phdu.getAxes();

  for (let i = 0; i < axes[1]; i++) {
    for (let j = 0; j < axes[0]; j++) {
      doSomething(data16b[i * axes[0] + j]);
    }
  }
}

open(process.argv[2]);
```

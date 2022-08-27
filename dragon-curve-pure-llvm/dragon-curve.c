#ifndef DRAGON_CURVE
#define DRAGON_CURVE

// helper for transforming turns into coordinates
// 0 1 0 -1....

int sign(int x) { return (x % 2) * (2 - (x % 4)); }

// -1 for left and 1 for right
// see https://en.wikipedia.org/wiki/Dragon_curve

int getTurn(int n)
{
  int turnFlag = (((n + 1) & -(n + 1)) << 1) & (n + 1);
  return turnFlag != 0 ? -1 : 1;
}

// fills source with x and y points [x0, y0, x1, y1,...]
void dragonCurve(double source[], int size, int len, double x0, double y0)
{
  int i, angle = 0;
  double x = x0, y = y0;
  for (i = 0; i < size; i++)
  {
    int turn = getTurn(i);
    angle = angle + turn;
    x = x - len * sign(angle);
    y = y - len * sign(angle + 1);
    source[2 * i] = x;
    source[2 * i + 1] = y;
  }
}
#endif

/**
docker run --rm -v $(pwd):$(pwd) -w $(pwd) zloymult/wasm-build-kit \
clang --target=wasm32 -O3 -nostdlib -Wl,--no-entry -Wl,--export-all -o dragon-curve.wasm dragon-curve.c


--target=wasm32 tells a compiler to use WebAssembly as a target for compilation.
-O3 applies a maximum amount of optimizations.
-nostdlib tells not to use system libraries, as they are useless in the context of a browser.
-Wl,--no-entry -Wl,--export-all are flags that tell the linker to export all the C functions we defined from the WebAssembly module and ignore the absence of main().


to inspect generated wasm file,
docker run --rm -v $(pwd):$(pwd) -w $(pwd) zloymult/wasm-build-kit \
wasm-objdump dragon-curve.wasm -s


We can reduce the size of our binary with an awesome tool called Bynarien that is a part of the WebAssembly toolchain.
docker run --rm -v $(pwd):$(pwd) -w $(pwd) zloymult/wasm-build-kit \
wasm-opt -Os dragon-curve.wasm -o dragon-curve-opt.wasm

to read wasm in text,
docker run --rm -v $(pwd):$(pwd) -w $(pwd) zloymult/wasm-build-kit \
wasm2wat dragon-curve-opt.wasm > dragon-curve-opt.wat
*/

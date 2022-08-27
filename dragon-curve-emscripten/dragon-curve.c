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
  The “pure LLVM” approach (in dragon-curve-llvm) is minimalistic on purpose; we compiled our program without system libraries. 
  We also manage memory in the most atrocious of possible ways: by calculating an offset to the heap. 
  That allowed us to demystify WebAssembly’s memory model. 
  In real-world applications, we want to allocate memory properly and use system libraries, where “system” is our browser: 
  WebAssembly still runs in the sandbox and has no direct access to your operating system.

  All of that can be done with the help of the emscripten: 
  a toolchain for compiling WebAssembly that takes care of simulating many system’s capabilities inside the browser: 
  working with STDIN, STDOUT, and filesystem, and even OpenGL graphics that gets automatically translated into WebGL. 
  It also integrates Bynarien that we used to slim down our binary, so we don’t have to worry about additional optimizations anymore.

  We went to the trouble of packaging ecmsripten into the Docker image for you, so you don’t have to install anything on your system to run the command below:
  docker run --rm -v $(pwd):$(pwd) -w $(pwd) zloymult/wasm-build-kit \
  emcc dragon-curve.c -Os -o dragon-curve.js \
  -s EXPORTED_FUNCTIONS='["_dragonCurve", "_malloc", "_free"]' \
  -s EXPORTED_RUNTIME_METHODS='["ccall"]' \
  -s MODULARIZE=1

  -Os tells emscripten to optimize for size: both for Wasm and JS
  Note that we only need to specify the .js file name as the output, .wasm is generated automatically.
  We can also choose which function we want to export from the resulting Wasm module, note that it requires an underscore before the name, hence -s EXPORTED_FUNCTIONS='["_dragonCurve", "_malloc", "_free"]'. The last two functions will help us work with memory.
  As our source code is C, we also have to export the ccall function that emscripten generates for us.
  MODULARIZE=1 allows us to use a global Module function that returns a Promise with an instance of our wasm module.
*/
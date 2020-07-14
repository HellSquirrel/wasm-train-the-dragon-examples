var Module = require('./dragon-curve.js');

function nativeDragonCurveSequence(order, length) {
  var length = (Math.pow(2, order) + 1) * 2;
  var sequence = new Float64Array(length);

  try {
    // Allocate memory and copy our blank array to it (to avoid problems with possible garbage)
    var memoryBuffer = Module._malloc(sequence.length * sequence.BYTES_PER_ELEMENT);
    Module.HEAPF64.set(sequence, memoryBuffer / sequence.BYTES_PER_ELEMENT);
    // Call C code
    Module.ccall('dragon_curve', null, ['number', 'number', 'number'], [order, length, memoryBuffer]);
    // Copy results from memory to JS array
    sequence.set(Module.HEAPF64.subarray(memoryBuffer / sequence.BYTES_PER_ELEMENT, memoryBuffer / sequence.BYTES_PER_ELEMENT + length));
  } finally {
    // Release memory
    Module._free(memoryBuffer);
  }

  return sequence;
}
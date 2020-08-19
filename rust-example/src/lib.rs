mod utils;

use wasm_bindgen::prelude::*;


// When the `wee_alloc` feature is enabled, use `wee_alloc` as the global
// allocator.
#[cfg(feature = "wee_alloc")]
#[global_allocator]
static ALLOC: wee_alloc::WeeAlloc = wee_alloc::WeeAlloc::INIT;

#[wasm_bindgen]
pub fn dragon_curve(size: u32, len: f64, x0: f64, y0: f64) -> Vec<f64>
{
  dragon_curve::dragon_curve(size, len, x0, y0)
}

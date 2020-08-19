(module
  (type (;0;) (func (param i32) (result i32)))
  (type (;1;) (func))
  (type (;2;) (func (param i32 i32 i32 f64 f64)))
  (func (;0;) (type 1)
    nop)
  (func (;1;) (type 0) (param i32) (result i32)
    i32.const 2
    local.get 0
    i32.const 4
    i32.rem_s
    i32.sub
    local.get 0
    i32.const 2
    i32.rem_s
    i32.mul)
  (func (;2;) (type 0) (param i32) (result i32)
    (local i32)
    i32.const -1
    i32.const 1
    local.get 0
    i32.const 1
    i32.add
    local.tee 1
    local.get 0
    i32.const -1
    i32.xor
    i32.and
    i32.const 1
    i32.shl
    local.get 1
    i32.and
    select)
  (func (;3;) (type 2) (param i32 i32 i32 f64 f64)
    (local i32 i32 i32)
    local.get 1
    i32.const 1
    i32.ge_s
    if  ;; label = @1
      loop  ;; label = @2
        local.get 0
        local.get 3
        i32.const -1
        i32.const 1
        local.get 5
        i32.const 1073741823
        i32.xor
        local.get 5
        i32.const 1
        i32.add
        local.tee 5
        i32.and
        i32.const 1
        i32.shl
        local.get 5
        i32.and
        select
        local.get 6
        i32.add
        local.tee 6
        i32.const 2
        i32.rem_s
        local.get 2
        i32.mul
        i32.const 2
        local.get 6
        i32.const 4
        i32.rem_s
        i32.sub
        i32.mul
        f64.convert_i32_s
        f64.sub
        local.tee 3
        f64.store
        local.get 0
        i32.const 8
        i32.add
        local.get 4
        local.get 6
        i32.const 1
        i32.add
        local.tee 7
        i32.const 2
        i32.rem_s
        local.get 2
        i32.mul
        i32.const 2
        local.get 7
        i32.const 4
        i32.rem_s
        i32.sub
        i32.mul
        f64.convert_i32_s
        f64.sub
        local.tee 4
        f64.store
        local.get 0
        i32.const 16
        i32.add
        local.set 0
        local.get 1
        local.get 5
        i32.ne
        br_if 0 (;@2;)
      end
    end)
  (memory (;0;) 2)
  (global (;0;) i32 (i32.const 1024))
  (global (;1;) i32 (i32.const 1024))
  (global (;2;) i32 (i32.const 1024))
  (global (;3;) i32 (i32.const 66560))
  (global (;4;) i32 (i32.const 0))
  (global (;5;) i32 (i32.const 1))
  (export "memory" (memory 0))
  (export "__wasm_call_ctors" (func 0))
  (export "sign" (func 1))
  (export "getTurn" (func 2))
  (export "dragonCurve" (func 3))
  (export "__dso_handle" (global 0))
  (export "__data_end" (global 1))
  (export "__global_base" (global 2))
  (export "__heap_base" (global 3))
  (export "__memory_base" (global 4))
  (export "__table_base" (global 5)))

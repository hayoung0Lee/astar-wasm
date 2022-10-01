# path-algorithm

## Reading Materials

- [What is Global Path Planning & How Does it Compare to Local Path Planning?](https://www.energid.com/blog/what-is-global-path-planning-how-does-it-compare-to-local-path-planning)

## WASM

- [WebAssembly Concepts](https://developer.mozilla.org/en-US/docs/WebAssembly/Concepts)
- [emscripten](https://emscripten.org/)
  - install cmake using `brew install cmake`
- [Calling a custom function defined in C](https://developer.mozilla.org/en-US/docs/WebAssembly/C_to_wasm#calling_a_custom_function_defined_in_c)
- [Porting from c/c++](https://developer.mozilla.org/en-US/docs/WebAssembly/Concepts#porting_from_cc)
  ```
  Emscripten first feeds the C/C++ into clang+LLVM — a mature open-source C/C++ compiler toolchain, shipped as part of XCode on OSX for example.
  Emscripten transforms the compiled result of clang+LLVM into a .wasm binary.
  By itself, WebAssembly cannot currently directly access the DOM; it can only call JavaScript, passing in integer and floating point primitive data types. Thus, to access any Web API, WebAssembly needs to call out to JavaScript, which then makes the Web API call. Emscripten therefore creates the HTML and JavaScript glue code needed to achieve this.
  ```

#include <iostream>
#include <emscripten/emscripten.h>

int main(int argc, char ** argv) {
    std::cout << "Hello World" << std::endl;
}

#ifdef __cplusplus
extern "C" {
#endif

EMSCRIPTEN_KEEPALIVE void myFunction(int argc, char ** argv) {
    printf("MyFunction Called\n");
}

#ifdef __cplusplus
}
#endif
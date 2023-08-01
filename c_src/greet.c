#include <stdio.h>
#include <emscripten/emscripten.h>

EMSCRIPTEN_KEEPALIVE 
void greet() {
  printf("Hello world from C!\n");
}

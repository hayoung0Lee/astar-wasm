#include <emscripten.h>
#include <emscripten/bind.h>
#include "map_manager.h"

using namespace emscripten;

// emcc --bind map_manager_bindings.cpp -Icpp/ *.cpp -s WASM=1 -s MODULARIZE=1 -o map_manager.js
// https://emscripten.org/docs/porting/connecting_cpp_and_javascript/embind.html
EMSCRIPTEN_BINDINGS(MapManager)
{
    class_<MapManager>("MapManager")
        .constructor<int, int>()
        .function("addObstacle", &MapManager::addObstacle)
        .function("removeObstacle", &MapManager::removeObstacle)
        .function("getMap", &MapManager::getMap);
}

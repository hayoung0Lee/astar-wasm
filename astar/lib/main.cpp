#include <iostream>
// #include <string.h>
// #include <cstdlib>
#include "map_manager.h"
#include "astar_pathfinder.h"
// #include <emscripten/bind.h>

using namespace std;

int main(int argc, char **argv)
{
  MapManager curMap(6, 6);
  curMap.addObstacle(1, 1);
  curMap.addObstacle(3, 4);
  curMap.addObstacle(2, 4);
  curMap.addObstacle(4, 5);
  curMap.printMap();

  AstarPathFinder astar(curMap.getMap());
  astar.getResult(true);
  cout << "Startttt! " << endl;
  // cout << "hello is it printed? " << endl;
}

// emcc -lembind -o ./map_manager.js ./map_manager.cpp
// emcc -lembind -o quick_example.js quick_example.cpp
// https://emscripten.org/docs/porting/connecting_cpp_and_javascript/embind.html
// EMSCRIPTEN_BINDINGS(stl_wrappers)
// {
//   emscripten::register_vector<int>("VectorInt");
//   emscripten::register_vector<vector<int>>("VectorVectorInt");

//   value_object<NodeWeight>("NodeWeight")
//       .field("id", &NodeWeight::id)
//       .field("fScore", &NodeWeight::fScore)
//       .field("gScore", &NodeWeight::gScore)
//       .field("hScore", &NodeWeight::hScore)
//       .field("parentId", &NodeWeight::parentId);

//   emscripten::register_vector<NodeWeight>("VectorNodeWeight");

//   // emscripten::register_vector<int>("VectorInt");
//   // emscripten::register_vector<vector<int>>("VectorVectorInt");
// }

// EMSCRIPTEN_BINDINGS(my_module)
// {
//   class_<MapManager>("MapManager")
//       .constructor<int, int>()
//       .constructor()
//       .function("addObstacle", &MapManager::addObstacle)
//       .function("removeObstacle", &MapManager::removeObstacle)
//       .function("getMap", &MapManager::getMap);

//   class_<AstarPathFinder>("AstarPathFinder")
//       .constructor<const vector<vector<int>> &>()
//       .function("getResult", &AstarPathFinder::getResult);
// }

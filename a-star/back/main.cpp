#include <iostream>
// #include <emscripten/emscripten.h>
// #include <string.h>
// #include <cstdlib>
#include "map_manager.h"
#include "astar_pathfinder.h"

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

  cout << "hello" << endl;
}

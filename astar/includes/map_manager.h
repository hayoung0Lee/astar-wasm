#ifndef MAP_MANAGER_H
#define MAP_MANAGER_H
#include <iostream>
#include <vector>
#include <emscripten/bind.h>
using namespace emscripten;
using namespace std;

class MapManager
{
private:
    int r;
    int c;
    vector<vector<int>> m;

public:
    MapManager(int row, int col);
    MapManager();
    ~MapManager();
    void addObstacle(int x, int y);
    void removeObstacle(int x, int y);
    void printMap() const;
    bool mapStatus(int x, int y);
    const vector<vector<int>> &getMap() const;
};

#endif

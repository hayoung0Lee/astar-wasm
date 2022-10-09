#include "map_manager.h"
/***
 * Map Manager
 ***/

MapManager::MapManager(int row, int col) : r(row), c(col)
{
    for (int i = 0; i < r; i++)
    {
        m.push_back(vector<int>(c));
    }
}

MapManager::MapManager()
    : r(10), c(10)
{
    MapManager(r, c);
}

MapManager::~MapManager() {}

void MapManager::addObstacle(int x, int y)
{
    if (x < 0 || x >= r || y < 0 || y >= c)
    {
        return;
    }
    if (x == 0 && y == 0)
    {
        return;
    }
    if (x == r - 1 && y == c - 1)
    {
        return;
    }
    m[x][y] = 1;
}

void MapManager::removeObstacle(int x, int y)
{
    if (x < 0 || x >= r || y < 0 || y >= c)
    {
        return;
    }
    m[x][y] = 0;
}

void MapManager::printMap() const
{
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            cout << m[i][j] << " ";
        }
        cout << endl;
    }
}

bool MapManager::mapStatus(int x, int y)
{
    return m[x][y] == 1;
}

const vector<vector<int>> &MapManager::getMap() const
{
    return m;
}

// // emcc -lembind -o ./map_manager.js ./map_manager.cpp
// // emcc -lembind -o quick_example.js quick_example.cpp
// // https://emscripten.org/docs/porting/connecting_cpp_and_javascript/embind.html
EMSCRIPTEN_BINDINGS(stl_wrappers)
{
    emscripten::register_vector<int>("VectorInt");
    emscripten::register_vector<vector<int>>("VectorVectorInt");
}

EMSCRIPTEN_BINDINGS(my_module)
{
    class_<MapManager>("MapManager")
        .constructor<int, int>()
        .constructor()
        .function("addObstacle", &MapManager::addObstacle)
        .function("removeObstacle", &MapManager::removeObstacle)
        .function("printMap", &MapManager::printMap)
        .function("mapStatus", &MapManager::mapStatus)
        .function("getMap", &MapManager::getMap);
}

// emcmake cmake .
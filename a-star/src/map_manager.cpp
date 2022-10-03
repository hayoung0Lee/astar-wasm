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

int MapManager::getRowSize() const
{
    return r;
}

int MapManager::getColSize() const
{
    return c;
}

const vector<vector<int>> &MapManager::getMap() const
{
    return m;
}
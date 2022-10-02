#include <iostream>
// #include <emscripten/emscripten.h>
#include <string.h>

#include <cstdlib>
#include <vector>

using namespace std;

class MapManager
{
public:
  int r;
  int c;
  int **m; // 2d array
  // vector<vector<int>> m(vector<int>);

  MapManager(int row, int col);

  MapManager();
  ~MapManager();
  void addObstacle(int x, int y);
  void removeObstacle(int x, int y);
  void printMap() const;
};

// https://life-with-coding.tistory.com/411
class AstarPathFinder
{
private:
  vector<pair<int, int>> cc;
  vector<pair<int, int>> oo;

public:
  AstarPathFinder();
  int getHeuristicValue(pair<int, int> a, pair<int, int> b) const;
  vector<pair<int, int>> findPath();
  vector<pair<int, int>> getResult();
};

AstarPathFinder::AstarPathFinder() { cc.push_back(pair<int, int>(0, 0)); }

int AstarPathFinder::getHeuristicValue(pair<int, int> a,
                                       pair<int, int> b) const
{
  return abs(a.first - b.first) + abs(a.second - b.second);
}

vector<pair<int, int>> AstarPathFinder::findPath()
{
  cout << "find path" << endl;
  return cc;
}

vector<pair<int, int>> AstarPathFinder::getResult()
{
  findPath();

  cout << "getResult test" << endl;

  return cc;
}

int main(int argc, char **argv)
{
  MapManager curMap(6, 6);
  curMap.addObstacle(2, 4);
  curMap.addObstacle(4, 5);
  curMap.printMap();

  AstarPathFinder astar;
  astar.getResult();

  cout << "Hello World" << endl;
}

MapManager::MapManager(int row, int col) : r(row), c(col)
{
  m = new int *[r];
  // https://stackoverflow.com/questions/936687/how-do-i-declare-a-2d-array-in-c-using-new
  for (int i = 0; i < r; i++)
  {
    m[i] = new int[c];
  }
}

MapManager::MapManager() : r(5), c(5)
{
  m = new int *[r];

  for (int i = 0; i < r; i++)
  {
    m[i] = new int[c];
  }
}

MapManager::~MapManager() { delete[] m; }

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

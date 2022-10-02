#include <iostream>
// #include <emscripten/emscripten.h>
#include <string.h>

#include <cstdlib>
#include <vector>
#include <queue>
#include <algorithm>

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
  int getRowSize() const;
  int getColSize() const;
  const vector<vector<int>> &getMap() const;
};

// https://life-with-coding.tistory.com/411
struct NodeWeight
{
  pair<int, int> id;
  int fScore;
  int gScore;
  int hScore;
  pair<int, int> parentId;
};

struct compare
{
  bool operator()(NodeWeight a, NodeWeight b)
  {
    return a.fScore < b.fScore;
  }
};

class AstarPathFinder
{
private:
  vector<NodeWeight> cc;
  // https://kbj96.tistory.com/15
  priority_queue<NodeWeight, vector<NodeWeight>, compare> oo;
  vector<NodeWeight> path;
  const vector<vector<int>> &m;
  int getHeuristicValue(pair<int, int> a, pair<int, int> b) const;
  const vector<NodeWeight> &findPath();

public:
  AstarPathFinder(const vector<vector<int>> &mapValue);
  const vector<NodeWeight> &getResult(bool cleanMode);
};

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
}

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

/***
 * A star
 ***/

AstarPathFinder::AstarPathFinder(const vector<vector<int>> &mapValue)
    : m(mapValue)
{
}

int AstarPathFinder::getHeuristicValue(pair<int, int> a,
                                       pair<int, int> b) const
{
  return abs(a.first - b.first) + abs(a.second - b.second);
}

const vector<NodeWeight> &AstarPathFinder::findPath()
{
  // first node
  NodeWeight n;
  n.id = pair<int, int>(0, 0);
  n.fScore = 0;
  n.gScore = 0;
  n.hScore = 0;
  cc.push_back(n);

  int r = m.size();
  int c = m[0].size();
  int dx[4] = {0, 1, 0, -1};
  int dy[4] = {1, 0, -1, 0};

  vector<vector<bool>> visited(r, vector<bool>(c, false));
  visited[0][0] = true;

  while (true)
  {
    NodeWeight current = cc.back();

    pair<int, int> cId = current.id;
    int c_gscore = current.gScore;

    if (cId.first == r - 1 && cId.second == c - 1)
    {
      break;
    }

    int next_gscore = c_gscore + 1;

    for (int i = 0; i < 4; i++)
    {
      int nx = cId.first + dx[i];
      int ny = cId.second + dy[i];

      if (nx < 0 || nx >= r || ny < 0 || ny >= c)
      {
        continue;
      }

      if (m[nx][ny] == 1)
      {
        // it is an obstacle.
        continue;
      }

      if (visited[nx][ny])
      {
        // Its weight is calcualted already by other node.
        // And because I am searching nodes in bfs way,
        // g value is always bigger or same if there was a previous node that accessed it here.
        continue;
      }

      NodeWeight nn;
      nn.id = pair<int, int>(nx, ny);

      nn.gScore = next_gscore;
      nn.hScore = getHeuristicValue(nn.id, pair<int, int>(r - 1, c - 1));

      nn.fScore = nn.gScore + nn.gScore;

      nn.parentId = current.id;
      oo.push(nn); // add to priority queue

      visited[nx][ny] = true;
    }

    // getSomething out of oo and put in in cc.
    cc.push_back(oo.top());
    oo.pop();
  }

  return cc;
}

const vector<NodeWeight> &AstarPathFinder::getResult(bool cleanMode)
{
  findPath();

  // loop cc and get path
  // Start
  // path.push_back(pair<int, int>(0, 0));

  if (cleanMode)
  {
    path.push_back(cc.back());
    pair<int, int> parentId = cc.back().parentId;

    for (int i = cc.size() - 2; i >= 0; i--)
    {
      pair<int, int> currentId = cc[i].id;

      if (currentId.first == parentId.first && currentId.second == parentId.second)
      {
        path.push_back(cc[i]);
        parentId = cc[i].parentId;
      }
    }
    reverse(path.begin(), path.end());
  }
  else
  {
    // add every thing -> how it calcualted the path
    for (int i = 0; i < cc.size(); i++)
    {
      path.push_back(cc[i]);
    }
  }

  for (int i = 0; i < path.size(); i++)
  {
    cout << path[i].id.first << " " << path[i].id.second << endl;
  }

  return path;
}

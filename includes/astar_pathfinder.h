#ifndef ASTAR_PATHFINDER_H
#define ASTAR_PATHFINDER_H
#include <emscripten/bind.h>
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace emscripten;
using namespace std;

// https://life-with-coding.tistory.com/411

struct Point
{
    int x;
    int y;
};

struct NodeWeight
{
    Point id;
    int fScore;
    int gScore;
    int hScore;
    Point parentId;
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
    vector<NodeWeight> path;
    const vector<vector<int>> &m;
    int getHeuristicValue(Point a, Point b) const;
    const vector<NodeWeight> findPath();

public:
    AstarPathFinder(const vector<vector<int>> &mapValue);
    const vector<NodeWeight> &getResult(bool cleanMode);
};

#endif
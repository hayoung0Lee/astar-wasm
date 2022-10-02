#ifndef ASTAR_PATHFINDER_H
#define ASTAR_PATHFINDER_H

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

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

#endif
#include "astar_pathfinder.h"

/***
 * A star
 ***/

AstarPathFinder::AstarPathFinder(const vector<vector<int>> &mapValue)
    : m(mapValue)
{
}

int AstarPathFinder::getHeuristicValue(Point a,
                                       Point b) const
{
    return abs(a.x - b.x) + abs(a.y - b.y);
}

const vector<NodeWeight> &AstarPathFinder::findPath()
{
    // first node
    NodeWeight n;
    n.id.x = 0;
    n.id.y = 0;
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

    int first = true;

    while (first || oo.size() > 0)
    {
        first = false; // for first step

        NodeWeight current = cc.back();

        Point cId = current.id;
        int c_gscore = current.gScore;

        if (cId.x == r - 1 && cId.y == c - 1)
        {
            break;
        }

        int next_gscore = c_gscore + 1;

        for (int i = 0; i < 4; i++)
        {
            int nx = cId.x + dx[i];
            int ny = cId.y + dy[i];

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
            nn.id.x = nx;
            nn.id.y = ny;

            nn.gScore = next_gscore;

            Point next;
            next.x = r - 1;
            next.y = c - 1;

            nn.hScore = getHeuristicValue(nn.id, next);

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

    int r = m.size();
    int c = m[0].size();
    NodeWeight last = cc.back();
    if (!(last.id.x == r - 1 && last.id.y == c - 1))
    {
        cout << "not found" << endl;
        return path;
    }

    if (cleanMode)
    {
        path.push_back(cc.back());
        Point parentId = cc.back().parentId;

        for (int i = cc.size() - 2; i >= 0; i--)
        {
            Point currentId = cc[i].id;

            if (currentId.x == parentId.x && currentId.y == parentId.y)
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
        cout << path[i].id.x << " " << path[i].id.y << endl;
    }

    return path;
}

EMSCRIPTEN_BINDINGS(stl_wrappers2)
{
    value_object<Point>("Point")
        .field("x", &Point::x)
        .field("y", &Point::y);

    value_object<NodeWeight>("NodeWeight")
        .field("id", &NodeWeight::id)
        .field("fScore", &NodeWeight::fScore)
        .field("gScore", &NodeWeight::gScore)
        .field("hScore", &NodeWeight::hScore)
        .field("parentId", &NodeWeight::parentId);

    emscripten::register_vector<NodeWeight>("VectorNodeWeight");
}

EMSCRIPTEN_BINDINGS(my_module2)
{
    class_<AstarPathFinder>("AstarPathFinder")
        .constructor<const vector<vector<int>> &>()
        .function("getResult", &AstarPathFinder::getResult);
}

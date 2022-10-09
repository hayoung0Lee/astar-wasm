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

const vector<NodeWeight> AstarPathFinder::findPath()
{
    int r = m.size();
    int c = m[0].size();

    // https://kbj96.tistory.com/15
    priority_queue<NodeWeight, vector<NodeWeight>, compare> open_list; // saves condidates
    vector<NodeWeight> close_list;                                     // saves processed node
    vector<vector<bool>> visited(r, vector<bool>(c, false));

    // first node
    NodeWeight n;
    n.id.x = 0;
    n.id.y = 0;
    n.fScore = 0;
    n.gScore = 0;
    n.hScore = 0;
    open_list.push(n);
    visited[0][0] = true;

    int dx[4] = {0, 1, 0, -1};
    int dy[4] = {1, 0, -1, 0};

    Point destination;
    destination.x = r - 1;
    destination.y = c - 1;

    while (open_list.size() > 0)
    {
        close_list.push_back(open_list.top());
        open_list.pop();

        NodeWeight current = close_list.back();

        // break because it reached to the destination
        Point cId = current.id;
        if (cId.x == r - 1 && cId.y == c - 1)
        {
            break;
        }

        int next_gscore = current.gScore + 1;

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

            NodeWeight next;
            next.id.x = nx;
            next.id.y = ny;
            next.gScore = next_gscore;
            next.hScore = getHeuristicValue(next.id, destination);
            next.fScore = next.gScore + next.gScore;
            next.parentId = current.id;
            open_list.push(next); // add to priority queue
            visited[nx][ny] = true;
        }
    }

    return close_list;
}

const vector<NodeWeight> &AstarPathFinder::getResult(bool cleanMode)
{
    const vector<NodeWeight> &close_list = findPath();

    int r = m.size();
    int c = m[0].size();
    NodeWeight last = close_list.back();
    if (!(last.id.x == r - 1 && last.id.y == c - 1))
    {
        cout << "not found" << endl;

        for (int i = 0; i < close_list.size(); i++)
        {
            cout << close_list[i].id.x << " " << close_list[i].id.y << endl;
        }
        return path;
    }

    if (cleanMode)
    {
        path.push_back(close_list.back());
        Point parentId = close_list.back().parentId;

        for (int i = close_list.size() - 2; i >= 0; i--)
        {
            Point currentId = close_list[i].id;

            if (currentId.x == parentId.x && currentId.y == parentId.y)
            {
                path.push_back(close_list[i]);
                parentId = close_list[i].parentId;
            }
        }
        reverse(path.begin(), path.end());
    }
    else
    {
        // add every thing -> how it calcualted the path
        for (int i = 0; i < close_list.size(); i++)
        {
            path.push_back(close_list[i]);
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

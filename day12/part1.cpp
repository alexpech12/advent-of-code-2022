#include <iostream>
#include <fstream>
#include <set>
#include <map>
#include <vector>

using namespace std;

// static const int MAP_WIDTH = 8;
// static const int MAP_HEIGHT = 5;
static const int MAP_WIDTH = 83;
static const int MAP_HEIGHT = 41;

class Point
{
public:
    int x, y, height;

    Point() {}

    Point(int x, int y, int height)
    {
        this->x = x;
        this->y = y;
        this->height = height;
    }

    void print() {
        cout << "["<<x<<","<<y<<"] = "<<height << endl;
    }

    bool operator==(const Point& other) const {
        return x == other.x && y == other.y;
    }

    int sortValue() const {
      return x + y * MAP_WIDTH;
    }

    bool operator< (const Point& other) const {
        return sortValue() < other.sortValue();
    }
};

void reconstruct_path(map<Point, Point> &cameFrom, Point current, vector<Point> &path) {
    path.push_back(current);
    while (cameFrom.count(current)) { // current in cameFrom.Keys:
        current = cameFrom[current];
        path.push_back(current);
    }
}

// **Copied straight from wikipedia**
// A* finds a path from start to goal.
// h is the heuristic function. h(n) estimates the cost to reach goal from node n.
void
A_Star(const Point (&heightMap)[MAP_WIDTH][MAP_HEIGHT], Point start, Point goal,
    int (*h)(Point&, Point&),
    vector<Point> &path)
{
    cout << "Starting A*..." << endl;

    // The set of discovered nodes that may need to be (re-)expanded.
    // Initially, only the start node is known.
    // This is usually implemented as a min-heap or priority queue rather than a hash-set.
    set<Point> openSet;
    openSet.insert(start);

    cout << "Open set size = " << openSet.size() << endl;

    // For node n, cameFrom[n] is the node immediately preceding it on the cheapest path from start
    // to n currently known.
    map<Point, Point> cameFrom; // an empty map

    // For node n, gScore[n] is the cost of the cheapest path from start to n currently known.
    map<Point, int> gScore; // map with default value of Infinity
    gScore[start] = 0;

    // For node n, fScore[n] := gScore[n] + h(n). fScore[n] represents our current best guess as to
    // how cheap a path could be from start to finish if it goes through n.
    map<Point, int> fScore; // map with default value of Infinity
    // fScore[start] = h(start);
    fScore[start] = h(start, goal);

    while (!openSet.empty())
    {
        // This operation can occur in O(Log(N)) time if openSet is a min-heap or a priority queue
        Point current; // the node in openSet having the lowest fScore[] value
        int min_score = INT_MAX;
        for (auto point : openSet)
        {
            int score = fScore[point];
            if (score < min_score)
            {
                min_score = score;
                current = point;
            }
        }
        cout << "Testing point ";
        current.print();

        if (current == goal)
        {
            reconstruct_path(cameFrom, current, path);
            return;
        }

        openSet.erase(current);

        vector<Point> neighbours;
        if(current.x > 0) {
            neighbours.push_back(heightMap[current.x-1][current.y]);
        }
        if(current.x < MAP_WIDTH-1) {
            neighbours.push_back(heightMap[current.x+1][current.y]);
        }
        if(current.y > 0) {
            neighbours.push_back(heightMap[current.x][current.y-1]);
        }
        if(current.y < MAP_HEIGHT-1) {
            neighbours.push_back(heightMap[current.x][current.y+1]);
        }

        for (auto neighbour : neighbours)
        {
            cout << "Testing neighbour ";
            neighbour.print();
            if (!gScore.count(current)) { gScore[current] = INT_MAX; }
            if (!gScore.count(neighbour)) { gScore[neighbour] = INT_MAX; }

            // for each neighbor of current
            // d(current,neighbor) is the weight of the edge from current to neighbor
            // tentative_gScore is the distance from start to the neighbor through current
            int weight = neighbour.height - current.height < 2 ? 1 : 1000000;
            cout << " - weight = " << weight << endl;

            int tentative_gScore = gScore[current] + weight;// d(current, neighbour);
            cout << " - gScore[current] = " << gScore[current] << endl;
            cout << " - gScore[neighbour] = " << gScore[neighbour] << endl;
            if (tentative_gScore < gScore[neighbour])
            {
                cout << " - Found a better path!" << endl;
                // This path to neighbor is better than any previous one. Record it!
                cameFrom[neighbour] = current;
                gScore[neighbour] = tentative_gScore;

                if (!fScore.count(current)) { fScore[neighbour] = INT_MAX; }
                fScore[neighbour] = tentative_gScore + h(neighbour, goal);
                cout << " - Inserted fScore for neighbour = " << fScore[neighbour] << endl;
                if (openSet.find(neighbour) == openSet.end())
                { // not in openSet
                    cout << " - Adding neighbour to open set..." << endl;
                    openSet.insert(neighbour);
                }
            }
        }
        cout << "Open set size = " << openSet.size() << endl;
        cout << endl;
    }
    // Open set is empty but goal was never reached
    // return; // failure
}

int main(int argc, char *argv[])
{
    ifstream MyFile(argv[1]);

    int result;
    string line;

    Point heightMap[MAP_WIDTH][MAP_HEIGHT];
    Point start, goal;

    int x = 0, y = 0;
    while (getline(MyFile, line))
    {
        cout << line << endl;

        x = 0;
        for (auto c : line)
        {
            if (c == 'S')
            {
                c = 'a' - 1;
                start = Point(x, y, c);
            }
            else if (c == 'E')
            {
                c = 'z' + 1;
                goal = Point(x, y, c);
            }

            heightMap[x][y] = Point(x, y, c);
            x++;
        }
        y++;
    }

    vector<Point> path;
    auto h = [](Point& p, Point& goal) {
        int x_diff = p.x - goal.x;
        int y_diff = p.y - goal.y;
        return MAP_WIDTH * MAP_HEIGHT - x_diff * x_diff + y_diff * y_diff;
    };
    A_Star(heightMap, start, goal, h, path);

    result = path.size() - 1;
    cout << "Path:" << endl;
    for(auto point : path) {
        point.print();
    }

    cout << "Path map:" << endl;
    for(int y = 0; y < MAP_HEIGHT; y++) {
        for(int x = 0; x < MAP_WIDTH; x++) {
            // Check if point in path
            Point current = heightMap[x][y];
            bool onPath = false;

            if (current == start) { cout << 'S'; continue; }
            if (current == goal) { cout << 'E'; continue; }

            for(int i = 1; i < path.size(); i++) {
                auto p = path[i];
                if (p == current) {
                    onPath = true;
                    // This point is in the path. Check direction.
                    auto prevPoint = path[i-1];
                    if (prevPoint.x < current.x) { cout << '<'; }
                    else if (prevPoint.x > current.x) { cout << '>'; }
                    else if (prevPoint.y < current.y) { cout << '^'; }
                    else if (prevPoint.y > current.y) { cout << 'V'; }
                    else { cout << '?'; }
                    break;
                }
            }
            if (!onPath) { cout << '.'; }
        }
        cout << endl;
    }
    cout << endl;
    cout << "Result = " << result << endl;

    MyFile.close();
}

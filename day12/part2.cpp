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

void add_unset_neighbours(
  const Point (&heightMap)[MAP_WIDTH][MAP_HEIGHT],
  const int (&distMap)[MAP_WIDTH][MAP_HEIGHT],
  Point p,
  set<Point> &neighbours) {

  if(p.x > 0 &&
     distMap[p.x-1][p.y] == -1 &&
     p.height - heightMap[p.x-1][p.y].height < 2) {
      neighbours.insert(heightMap[p.x-1][p.y]);
  }
  if(p.x < MAP_WIDTH-1 &&
     distMap[p.x+1][p.y] == -1 &&
     p.height - heightMap[p.x+1][p.y].height < 2) {
      neighbours.insert(heightMap[p.x+1][p.y]);
  }
  if(p.y > 0 &&
     distMap[p.x][p.y-1] == -1 &&
     p.height - heightMap[p.x][p.y-1].height < 2) {
      neighbours.insert(heightMap[p.x][p.y-1]);
  }
  if(p.y < MAP_HEIGHT-1 &&
     distMap[p.x][p.y+1] == -1 &&
     p.height - heightMap[p.x][p.y+1].height < 2) {
      neighbours.insert(heightMap[p.x][p.y+1]);
  }
}

void generate_dist_map(
  const Point (&heightMap)[MAP_WIDTH][MAP_HEIGHT],
  Point start,
  int (&distMap)[MAP_WIDTH][MAP_HEIGHT]) {
  /** Algorithm
   * Start from goal. It is value 0.
   * For each neighbour that is only 1 step away (not a 'wall') it gets value 1.
   * For each neighbour of 1s that is not a 'wall', it gets value 2.
   * Etc,
   */

  // Initialise distMap
  for(int y = 0; y < MAP_HEIGHT; ++y) {
    for(int x = 0; x < MAP_WIDTH; ++x) {
      distMap[x][y] = -1;
    }
  }

  int step = 0;
  distMap[start.x][start.y] = 0;

  set<Point> openSet;
  openSet.insert(start);

  while(!openSet.empty()) {
    auto neighbourSet = set<Point>();
    for(auto p : openSet) {
      distMap[p.x][p.y] = step;
      add_unset_neighbours(heightMap, distMap, p, neighbourSet);
    }
    // Replace openSet with neighbourSet
    openSet = neighbourSet;
    step++;
  }
}

int main(int argc, char *argv[])
{
    ifstream MyFile(argv[1]);

    int result;
    string line;

    Point heightMap[MAP_WIDTH][MAP_HEIGHT];
    // Map to hold number of steps from goal for each point
    int distMap[MAP_WIDTH][MAP_HEIGHT];
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

    // Generate map from goal since goal is stationary and start is moving
    generate_dist_map(heightMap, goal, distMap);
    for(int y = 0; y < MAP_HEIGHT; y++) {
        for(int x = 0; x < MAP_WIDTH; x++) {
            cout << distMap[x][y] << ' ';
        }
        cout << endl;
    }
    cout << endl;

    // Find the location with value 'a' and smallest number of steps from goal
    Point min_point;
    int min_dist = INT_MAX;
    for(int y = 0; y < MAP_HEIGHT; y++) {
        for(int x = 0; x < MAP_WIDTH; x++) {
            auto point = heightMap[x][y];
            if (point.height != 'a') continue;

            auto dist = distMap[x][y];
            if (dist == -1) continue;

            if(distMap[x][y] < min_dist) {
              min_dist = distMap[x][y];
              min_point = point;
            }
        }
    }
    result = min_dist;

    cout << "Result = " << result << endl;

    MyFile.close();
}

#include <iostream>
#include <fstream>
#include <set>

using namespace std;

int sign(int x) { return (x > 0) - (x < 0); }

class RopeState {
  public:
    int hx = 0, hy = 0, tx = 0, ty = 0;

    void move(int x, int y) {
      hx += x;
      hy += y;
      _updateTail();
    }

    pair<int, int> tailLocation() {
      return pair<int, int>(tx, ty);
    }

  private:
    void _updateTail() {
      cout << "Head at (" <<hx <<","<<hy<<"), tail at ("<<tx<<","<<ty<<")" << endl;
      int xdiff = hx - tx;
      int ydiff = hy - ty;

      if (abs(xdiff) < 2 && abs(ydiff) < 2) { return; }

      if (abs(ydiff) == 0) {
        // Horizontally aligned. Move horizontally.
        tx += xdiff - sign(xdiff);
      }
      else if (abs(xdiff) == 0) {
        // Vertically aligned. Move vertically.
        ty += ydiff - sign(ydiff);
      }
      else {
        // Moving diagonally.
        tx += sign(xdiff);
        ty += sign(ydiff);
      }
      cout << "Moving tail to ("<<tx<<","<<ty<<")" << endl;
    }
};

int main(int argc, char *argv[]) {
  ifstream MyFile(argv[1]);

  string line;

  set<pair<int, int>> visited;

  RopeState state;

  while (getline(MyFile, line)) {
    cout << line << endl;

    int steps = stoi(line.substr(2));
    switch(line[0]) {
      case 'L':
        for(int i = 0; i < steps; ++i) {
          state.move(-1, 0);
          visited.insert(state.tailLocation());
        }
        break;
      case 'R':
        for(int i = 0; i < steps; ++i) {
          state.move(1, 0);
          visited.insert(state.tailLocation());
        }
        break;
      case 'U':
        for(int i = 0; i < steps; ++i) {
          state.move(0, 1);
          visited.insert(state.tailLocation());
        }
        break;
      case 'D':
        for(int i = 0; i < steps; ++i) {
          state.move(0, -1);
          visited.insert(state.tailLocation());
        }
        break;
    }
  }

  cout << "result = " << visited.size() << endl;

  MyFile.close();
}

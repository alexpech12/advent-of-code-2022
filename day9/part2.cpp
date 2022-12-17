#include <iostream>
#include <fstream>
#include <set>
#include <vector>

using namespace std;

int sign(int x) { return (x > 0) - (x < 0); }

class RopeState {
  public:
    int hx = 0, hy = 0;
    int length;

    vector<int> tx, ty;

    RopeState(int length) {
      this->length = length;
      for(int i = 0; i < length; ++i) {
        tx.push_back(0);
        ty.push_back(0);
      }
    }

    void move(int x, int y) {
      hx += x;
      hy += y;
      _updateTail();
    }

    pair<int, int> tailLocation() {
      return pair<int, int>(tx[length-1], ty[length-1]);
    }

  private:
    void _updateTail() {
      for(int i = 0; i < length; i++) {
        _updateTailSegment(i);
      }
    }

    void _updateTailSegment(int i) {
      cout << "Head at (" <<hx <<","<<hy<<"), tail[" << i << "] at ("<<tx[i]<<","<<ty[i]<<")" << endl;
      int beginx = i == 0 ? hx : tx[i-1];
      int beginy = i == 0 ? hy : ty[i-1];
      int xdiff = beginx - tx[i];
      int ydiff = beginy - ty[i];

      if (abs(xdiff) < 2 && abs(ydiff) < 2) { return; }

      if (abs(ydiff) == 0) {
        // Horizontally aligned. Move horizontally.
        tx[i] += xdiff - sign(xdiff);
      }
      else if (abs(xdiff) == 0) {
        // Vertically aligned. Move vertically.
        ty[i] += ydiff - sign(ydiff);
      }
      else {
        // Moving diagonally.
        tx[i] += sign(xdiff);
        ty[i] += sign(ydiff);
      }
      cout << "Moving tail[" << i << "] to ("<<tx[i]<<","<<ty[i]<<")" << endl;
    }
};

int main(int argc, char *argv[]) {
  ifstream MyFile(argv[1]);

  string line;

  set<pair<int, int>> visited;

  RopeState state = RopeState(9);

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

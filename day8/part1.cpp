#include <iostream>
#include <fstream>

using namespace std;

// static const int SIZE_X = 5;
// static const int SIZE_Y = 5;
static const int SIZE_X = 99;
static const int SIZE_Y = 99;

bool tree_visible(int (&trees)[SIZE_X][SIZE_Y], int x_start, int y_start) {
  int tree_height = trees[x_start][y_start];

  // Traverse left
  bool visible = true;
  int x = x_start - 1;
  int y = y_start;
  while(x >= 0) {
    visible = trees[x][y] < tree_height;
    if (!visible) { break; }
    x--;
  }
  if (visible) return true;

  // Traverse right
  visible = true;
  x = x_start + 1;
  y = y_start;
  while(x < SIZE_X) {
    visible = trees[x][y] < tree_height;
    if (!visible) { break; }
    x++;
  }
  if (visible) return true;

  // Traverse up
  visible = true;
  x = x_start;
  y = y_start - 1;
  while(y >= 0) {
    visible = trees[x][y] < tree_height;
    if (!visible) { break; }
    y--;
  }
  if (visible) return true;

  // Traverse down
  visible = true;
  x = x_start;
  y = y_start + 1;
  while(y < SIZE_Y) {
    visible = trees[x][y] < tree_height;
    if (!visible) { break; }
    y++;
  }

  return visible;
}

int main(int argc, char *argv[]) {
  ifstream MyFile(argv[1]);

  string line;

  int trees[SIZE_X][SIZE_Y];

  int y = 0;
  while (getline(MyFile, line)) {
    cout << line << endl;

    for(int x = 0; x < SIZE_X; x++) {
      trees[x][y] = stoi(line.substr(x,1));
    }
    y++;
  }

  int visible_count = 2 * SIZE_X + 2 * SIZE_Y - 4;

  for(int y = 1; y < SIZE_Y - 1; y++) {
    for(int x = 1; x < SIZE_X - 1; x++) {
      if (tree_visible(trees, x, y)) {
        visible_count++;
      }
    }
  }

  cout << "visible_count = " << visible_count << endl;

  MyFile.close();
}

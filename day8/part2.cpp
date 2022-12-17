#include <iostream>
#include <fstream>

using namespace std;

// static const int SIZE_X = 5;
// static const int SIZE_Y = 5;
static const int SIZE_X = 99;
static const int SIZE_Y = 99;

int scenic_score(int (&trees)[SIZE_X][SIZE_Y], int x_start, int y_start) {
  int tree_height = trees[x_start][y_start];

  int score = 1;

  // Traverse left
  int visible_trees = 0;
  int x = x_start - 1;
  int y = y_start;
  while(x >= 0) {
    visible_trees++;
    if (trees[x][y] >= tree_height) { break; }

    x--;
  }
  score *= visible_trees;

  // Traverse right
  visible_trees = 0;
  x = x_start + 1;
  y = y_start;
  while(x < SIZE_X) {
    visible_trees++;
    if (trees[x][y] >= tree_height) { break; }

    x++;
  }
  score *= visible_trees;

  // Traverse up
  visible_trees = 0;
  x = x_start;
  y = y_start - 1;
  while(y >= 0) {
    visible_trees++;
    if (trees[x][y] >= tree_height) { break; }

    y--;
  }
  score *= visible_trees;

  // Traverse down
  visible_trees = 0;
  x = x_start;
  y = y_start + 1;
  while(y < SIZE_Y) {
    visible_trees++;
    if (trees[x][y] >= tree_height) { break; }

    y++;
  }
  score *= visible_trees;

  return score;
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

  int scenic_scores[SIZE_X][SIZE_Y];
  int max_scenic_score = 0;
  int max_scenic_score_x = -1;
  int max_scenic_score_y = -1;

  for(int y = 1; y < SIZE_Y - 1; y++) {
    for(int x = 1; x < SIZE_X - 1; x++) {
      int score = scenic_score(trees, x, y);
      cout << "scenic_score at [" << x << "," << y << "] = " << score << endl;

      if (score > max_scenic_score) {
        max_scenic_score = score;
        max_scenic_score_x = x;
        max_scenic_score_y = y;
      }
    }
  }

  cout << "max_scenic_score = " << max_scenic_score << " at [" << max_scenic_score_x << "," << max_scenic_score_y << "]" << endl;

  MyFile.close();
}

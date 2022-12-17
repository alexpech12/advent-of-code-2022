#include <iostream>
#include <fstream>

using namespace std;

static const int SCREEN_WIDTH = 40;
static const int SCREEN_HEIGHT = 6;

int main(int argc, char *argv[]) {
  ifstream MyFile(argv[1]);

  string line;

  int x_reg = 1;
  int cycles = 0;

  char screen[SCREEN_WIDTH][SCREEN_HEIGHT];

  auto update_screen = [](char (&screen)[SCREEN_WIDTH][SCREEN_HEIGHT], int cycles, int x_reg) {
    int x_pos = (cycles-1) % SCREEN_WIDTH;
    int y_pos = (cycles-1) / SCREEN_WIDTH;
    // cout << "Updating screen ["<<x_pos<<","<<y_pos<<"] = "<<(abs(x_pos - x_reg) <= 1 ? '#' : '.')<<"\n";
    screen[x_pos][y_pos] = abs(x_pos - x_reg) <= 1 ? '#' : '.';
  };

  while (getline(MyFile, line) && cycles < SCREEN_WIDTH * SCREEN_HEIGHT) {
    cout << line << endl;

    if(strncmp(line.c_str(), "noop", 4) == 0) {
      cycles += 1;
      update_screen(screen, cycles, x_reg);
    }
    else {
      int val = stoi(line.substr(5));
      cycles += 1;
      update_screen(screen, cycles, x_reg);

      cycles += 1;
      update_screen(screen, cycles, x_reg);

      x_reg += val;
    }
  }

  for(int y = 0; y < SCREEN_HEIGHT; ++y) {
    for(int x = 0; x < SCREEN_WIDTH; ++x) {
      cout << screen[x][y];
    }
    cout << endl;
  }

  MyFile.close();
}

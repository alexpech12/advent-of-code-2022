#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char *argv[]) {
  ifstream MyFile(argv[1]);

  string line;

  int x_reg = 1;
  int cycles = 0;
  int signal_strength_sum = 0;
  while (getline(MyFile, line)) {
    cout << line << endl;

    if(strncmp(line.c_str(), "noop", 4) == 0) {
      cycles += 1;
      if ((cycles - 20) % 40 == 0) {
        // Get signal strength
        cout << "Adding signal strength " << cycles * x_reg << " to " << signal_strength_sum << " at cycle " << cycles << "with x_reg = " << x_reg << endl;
        signal_strength_sum += cycles * x_reg;
      }
    }
    else {
      int val = stoi(line.substr(5));
      cycles += 1;
      if ((cycles - 20) % 40 == 0) {
        // Get signal strength
        cout << "Adding signal strength " << cycles * x_reg << " to " << signal_strength_sum << " at cycle " << cycles << "with x_reg = " << x_reg << endl;
        signal_strength_sum += cycles * x_reg;
      }
      cycles += 1;
      if ((cycles - 20) % 40 == 0) {
        // Get signal strength
        cout << "Adding signal strength " << cycles * x_reg << " to " << signal_strength_sum << " at cycle " << cycles << "with x_reg = " << x_reg << endl;
        signal_strength_sum += cycles * x_reg;
      }
      x_reg += val;
    }
  }

  cout << "signal_strength_sum = " << signal_strength_sum << endl;

  MyFile.close();
}

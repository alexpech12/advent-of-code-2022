#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int priority(char c) {
  return c >= 97 ? c - 96 : c - 38;
}

int main(int argc, char *argv[]) {
  ifstream MyFile(argv[1]);

  int prioritySum = 0;
  bool matched = false;
  string line;
  while (getline(MyFile, line)) {
    cout << line << endl;
    auto l1 = line.substr(0, line.length() / 2);
    auto l2 = line.substr(line.length() / 2, line.length() - 1);
    cout << l1 << ", " << l2 << endl;
    matched = false;
    for(auto c2 : l2) {
      for(auto c1 : l1) {
        if (c1 == c2) {
          matched = true;
          prioritySum += priority(c1);
          cout << "Matched " << c1 << ", adding priority " << priority(c1) << endl;
          break;
        }
      }
      if (matched)
        break;
    }
    cout << endl;
  }

  cout << "Priority sum = " << prioritySum << endl;

  MyFile.close();
}

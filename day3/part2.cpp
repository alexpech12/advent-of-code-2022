#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int priority(char c) {
  return c >= 97 ? c - 96 : c - 38;
}

string common_chars(string str1, string str2) {
  string common = "";
  for(char c : str2) {
    if(str1.find(c) != -1) {
      common.push_back(c);
    }
  }
  return common;
}

int main(int argc, char *argv[]) {
  ifstream MyFile(argv[1]);

  int prioritySum = 0;
  bool matched = false;
  string line;
  string lines[3];
  int i = 0;

  while (getline(MyFile, line)) {
    lines[i++] = line;
    if (i < 3)
      continue;
    else
      i = 0;

    // cout << lines[0] << endl << lines[1] << endl << lines[2] << endl;

    auto common = common_chars(lines[0], lines[1]);
    // cout << "Common1: " << common << endl;
    common = common_chars(common, lines[2]);
    // cout << "Common2: " << common << endl;
    prioritySum += priority(common[0]);
  }

  cout << "Priority sum = " << prioritySum << endl;

  MyFile.close();
}

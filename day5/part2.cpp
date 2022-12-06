#include <iostream>
#include <fstream>
#include <regex>
#include <vector>

using namespace std;

void performInstruction(int move, int from, int to, vector<vector<char>> *crates) {
  auto tmpStack = vector<char>();
  for(int i = 0; i < move; i++) {
    tmpStack.push_back((*crates)[from-1].back());
    (*crates)[from-1].pop_back();
  }
  for(int i = 0; i < move; i++) {
    (*crates)[to-1].push_back(tmpStack.back());
    tmpStack.pop_back();
  }
}

int main(int argc, char *argv[]) {
  ifstream MyFile(argv[1]);

  string line;
  vector<vector<char>> crateLines;
  while (getline(MyFile, line)) {
    if (line == "") break;

    auto crateRow = vector<char>();
    for(int i = 1; i < line.length(); i += 4) { crateRow.push_back(line[i]); }
    crateLines.push_back(crateRow);
  }

  vector<vector<char>> crateStacks;
  while(crateLines.size() > 0) {
    auto crateLine = crateLines.back();
    crateLines.pop_back();
    for(int i = 0; i < crateLine.size(); i++) {
      if(crateLine[i] == ' ') continue;

      if (i >= crateStacks.size()) { crateStacks.push_back(vector<char>()); }
      crateStacks[i].push_back(crateLine[i]);
    }
  }

  vector<int*> instructions;
  static std::regex const matcher( "move (\\d*) from (\\d*) to (\\d*)" );
  smatch regexResult;
  while (getline(MyFile, line)) {
    regex_search(line, regexResult, matcher);
    instructions.push_back(new int[3] {
      stoi(regexResult.str(1)),
      stoi(regexResult.str(2)),
      stoi(regexResult.str(3))
    });
  }
  cout << "Instructions:" << endl;
  for(auto i : instructions) {
    cout << "Move " << i[0] << " from " << i[1] << " to " << i[2] << endl;

    performInstruction(i[0], i[1], i[2], &crateStacks);

    cout << "Crate stacks:" << endl;
    for(auto c : crateStacks) {
      for(auto r : c) {
        cout << r << ", ";
      }
      cout << endl;
    }
  }

  for(auto stack : crateStacks) { cout << stack.back(); }
  cout << endl;

  for (auto i : instructions) { delete[] i; }
  MyFile.close();
}

#include <iostream>
#include <fstream>
#include <regex>

using namespace std;

int main(int argc, char *argv[]) {
  ifstream MyFile(argv[1]);

  static std::regex const matcher( "(\\d*)-(\\d*),(\\d*)-(\\d*)" );
  smatch regexResult;

  int result = 0;

  string line;
  while (getline(MyFile, line)) {
    regex_search(line, regexResult, matcher);
    int min1 = stoi(regexResult.str(1));
    int max1 = stoi(regexResult.str(2));
    int min2 = stoi(regexResult.str(3));
    int max2 = stoi(regexResult.str(4));
    if (!(min1 > max2 || min2 > max1))
      result++;
  }

  cout << "Result = " << result << endl;

  MyFile.close();
}

#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char *argv[]) {
  ifstream MyFile(argv[1]);

  int result;
  string line;

  while (getline(MyFile, line)) {
    cout << line << endl;
    for(auto i = 3; i < line.length(); i++) {
      cout << line[i-3] << ",";
      cout << line[i-2] << ",";
      cout << line[i-1] << ",";
      cout << line[i] << endl;
      if (
        line[i-3] != line[i-2] &&
        line[i-3] != line[i-1] &&
        line[i-3] != line[i] &&
        line[i-2] != line[i-1] &&
        line[i-2] != line[i] &&
        line[i-1] != line[i]
      ) {
        result = i + 1;
        break;
      }
    }
  }

  cout << "Result = " << result << endl;

  MyFile.close();
}
